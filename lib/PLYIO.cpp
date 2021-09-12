#include "../include/PLYIO.h"

PLYIO::PLYIO(){
    this->is_file_set = false;
    this->NumOfOutFile = 10;
}

PLYIO::~PLYIO(){}

void PLYIO::setFileName(char const* filename){
    this->_in_file = filename;
    this->is_file_set = true;
}

void PLYIO::setNumOfOutFile(size_t NumOfOutFile){
    this->NumOfOutFile = NumOfOutFile;
    // this->is_out_num_file_set = true;
}

void PLYIO::loadPLY(){
    file_open = fopen(_in_file.c_str(),"rb");
    char strOfLine[1024];   // 读取行的内容
    char endHeadFlag[] = "end_header "; // 头文件结束标志
    char numOfPointFlag[] = "element vertex ";  // 点的个数，字符型
    char numOfPoint[100];    // 主要用来读header中point的个数，看文件中有多少个点
    
    if (file_open == NULL)
    {
        cout << "Error:Open file fail!" << endl;
    }
    
    while (!feof(file_open))
    {
        fgets(strOfLine,1024,file_open);
        if (strlen(strOfLine) == strlen(endHeadFlag))
        {
            break;
        }
        if ((strstr(strOfLine,numOfPointFlag)) != NULL )
        {
            int startStrNum = strlen(numOfPointFlag);
			int subStrNumLen = strlen(strOfLine) - strlen(numOfPointFlag);
			for (int i = 0; i < subStrNumLen; i++)
			{
				numOfPoint[i] = strOfLine[startStrNum + i];    //从第start+i个元素开始向数组内赋值
			}
			this->numOfPoint = atol(numOfPoint);
        }
    }   
}

void PLYIO::dividePLY(){
    size_t slidSizeOfPoint = this->numOfPoint / this->NumOfOutFile;
    // Point_XYZ *pts = new Point_XYZ[slidSizeOfPoint];
    Point_XYZ* pts = (Point_XYZ*)malloc(slidSizeOfPoint*sizeOfPoint);
    for (size_t i = 0; i < this->NumOfOutFile; i++)
    {
        // if (i == (this->NumOfOutFile -1))
        // {
            // slidSizeOfPoint = this->numOfPoint - i * slidSizeOfPoint;
        // }
        fread(pts,sizeOfPoint,slidSizeOfPoint,file_open);
        char* fileName;
        string fileName1;
        fileName1 = "/home/ouong/WorkSpace/BAGs/DividedMap/ShanghaiTech_"+ to_string(i) + ".ply";
        fileName = (char*)fileName1.c_str();
        PLYIO::saveMap(pts,fileName,slidSizeOfPoint);
        // free(pts);
    } 
    delete[] pts; 


    // 最后一个文件
    slidSizeOfPoint = this->numOfPoint - slidSizeOfPoint * this->NumOfOutFile;
    // pts = (Point_XYZ*)malloc(slidSizeOfPoint*sizeOfPoint);
    pts = (Point_XYZ*)malloc(slidSizeOfPoint*sizeOfPoint);
    fread(pts,sizeOfPoint,slidSizeOfPoint,file_open);
    char* fileName;
    string fileName1;
    fileName1 = "/home/ouong/WorkSpace/BAGs/DividedMap/ShanghaiTech_"+ to_string(this->NumOfOutFile) + ".ply";
    fileName = (char*)fileName1.c_str();
    PLYIO::saveMap(pts,fileName,slidSizeOfPoint);
    fclose(this->file_open);
    delete[] pts; 
}

void PLYIO::saveMap(Point_XYZ *point, char *fileName, size_t numOfPoint){
    int elementNum = numOfPoint;
    FILE *fp;
    if ((fp = fopen(fileName, "wb")) == NULL) 
    {
        cout << "Error: cann't open the out files" << endl;
    }
    fprintf(fp,"ply\n");
    fprintf(fp, "format binary_little_endian 1.0\n");
	fprintf(fp, "comment File generated v1.0 (xiaojzh)\n");
	fprintf(fp, "element vertex %d\n", elementNum);
	fprintf(fp, "property float x\n");
	fprintf(fp, "property float y\n");
	fprintf(fp, "property float z\n");
    fprintf(fp, "property uchar red\n");
    fprintf(fp, "property uchar green\n");
    fprintf(fp, "property uchar blue\n");
	fprintf(fp, "end_header\n");
    // for (size_t i = 0; i < numOfPoint; i++)
    // {
    //     fwrite(*point[i],sizeof(Point_XYZ),1,fp);
    // }
    fwrite(point,sizeof(Point_XYZ),numOfPoint,fp);
    fclose(fp);
}

bool PLYIO::run(){
    if (!is_file_set)
    {
        cout << "Fail to set the file, pls to comform!!!" << endl;
        return false;
    }
    
    PLYIO::loadPLY();
    PLYIO::dividePLY();
    return true;
}

void PLYIO::divideNvoxel(string& inFile,string& outFile, size_t voxel_size){
    this->_in_file = inFile;
    this->_out_file = outFile;
    loadPLY();
    // 分配内存空间
    float* pts_xyz = (float*) malloc (3*sizeof(float));
    unsigned char* pts_rgb = (unsigned char*) malloc (3*sizeof(unsigned char));
    
    int index_x, index_y;    // 根据点的位置，进行分配
    // 记录最大的以及最小的，之后方便添加header
    // int index_x_max = -100000,
        // index_x_min = 100000,
        // index_y_max = -100000,
        // index_y_min = 100000;    // 如果检索的话，x最大值不一定匹配y的最大值
    string fileName;            // 输出文件名，命名原则是根据点云中起始点
    char line[LENGTH_OF_LINE];
    for (size_t i = 0; i < this->sizeOfPoint; i++)
    {          
        fread(pts_xyz,3,sizeof(float),file_open);
        fread(pts_rgb,3,sizeof(unsigned char),file_open);
        // 需要考虑点在负坐标轴
        index_x = (pts_xyz[0] < 0) ? (pts_xyz[0] / float(voxel_size) - 1) : (pts_xyz[0] / float(voxel_size));
        index_y = (pts_xyz[1] < 0) ? (pts_xyz[1] / float(voxel_size) - 1) : (pts_xyz[1] / float(voxel_size));
        
        fileName = this->_out_file + "/" + "ShanghaiTech_" + to_string(index_x) + "_" + to_string(index_y);
        FILE *fp;
        if ((fp = fopen(fileName.c_str(), "wb")) == NULL) 
        {
            cout << "Error: cann't open the out files" << endl;
        }
        fwrite(pts_xyz,3,sizeof(float),fp);
        fwrite(pts_rgb,3,sizeof(unsigned char),fp);
        fclose(fp);

        // 所以依然选择利用一个检索文件进行维护输出文件列表，这样方便后面添加header
        bool is_first_open = true;
        char line[LENGTH_OF_LINE];
        FILE* index_fp;
        string index_file = _out_file + "/indexOutFile.dat";
        if ((index_fp = fopen(index_file.c_str(),"ab+"))==NULL)
        {
            cout << "Error: cann't open the index file" << endl;
        }
        while (fgets(line,LENGTH_OF_LINE,index_fp))
        {
            if (strstr(line,fileName.c_str()) != NULL)
            {
                is_first_open = false;
                break;
            }
        } // 用一个数组进行维护，index[x*100+y] = 1,表示存在这个文件，再进行解码
    }
}

void writeHeader(char* filename){
    FILE* fp = fopen();
}