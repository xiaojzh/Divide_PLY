#include "../include/PLYIO.h"

PLYIO::PLYIO(){
    this->is_in_file_set = false;
    this->numOfOutFile = 10;
}

PLYIO::~PLYIO(){}

void PLYIO::loadPLY(){
    char const* filename = this->_in_file.c_str();
    file_open = fopen(filename,"rb");
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

void PLYIO::saveMap(Point_XYZ *point, char *fileName, size_t numOfPoint){
    int elementNum = numOfPoint;    // 点的个数
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

    // 改变了这里的sizeofpoint
    fwrite(point,sizeOfPoint,numOfPoint,fp);
    fclose(fp);
}

void PLYIO::divideNPLY(string& inFile, string& outFile, size_t numOfOutFile){
    // 读取文件名称
    this->_in_file = inFile; 
    // 查看是否满足文件名的要求
    if (!(EndWith(_in_file,".pcd") || EndWith(_in_file,".PCD")))
    {
        cout << "ERROR: the file name is not end with .pcd" << endl;
        return;
    }
    this->is_in_file_set = true;
    this-> numOfOutFile = numOfOutFile;
    if (this->numOfOutFile < 1)
    {
        cout << "ERROE: make sure the n > 0" << endl;
        return;
    }
    // 读取文件
    loadPLY();
    size_t slidSizeOfPoint = this->numOfPoint / this->numOfOutFile;
    Point_XYZ* pts = (Point_XYZ*)malloc(slidSizeOfPoint*sizeOfPoint);
    for (size_t i = 0; i < this->numOfOutFile; i++)
    {

        fread(pts,sizeOfPoint,slidSizeOfPoint,file_open);
        char* fileName;
        string fileName1;
        fileName1 = outFile + "/ShanghaiTech_"+ to_string(i) + ".ply";
        fileName = (char*)fileName1.c_str();
        PLYIO::saveMap(pts,fileName,slidSizeOfPoint);
    } 
    delete[] pts; 

 //    // 最后一个文件 (这个文件的点数很少，可以忽略)
 //    slidSizeOfPoint = this->numOfPoint - slidSizeOfPoint * this->numOfOutFile;
 //    // pts = (Point_XYZ*)malloc(slidSizeOfPoint*sizeOfPoint);
 //     pts = (Point_XYZ*)malloc(slidSizeOfPoint*sizeOfPoint);
 //     fread(pts,sizeOfPoint,slidSizeOfPoint,file_open);
 //     char* fileName;
 //     string fileName1;
 //     fileName1 = "/home/ouong/WorkSpace/BAGs/DividedMap/ShanghaiTech_"+ to_string(this->numOfOutFile) + ".ply";
 //     fileName = (char*)fileName1.c_str();
 //     PLYIO::saveMap(pts,fileName,slidSizeOfPoint);
 //     fclose(this->file_open);
 //     delete[] pts; 
}

void PLYIO::divideNsize(string& inFile, string& outFile, size_t sizeOfOutFile){
    // 转为n个文件
    this->sizeOfOutFile = sizeOfOutFile;
    loadPLY();
    size_t numOfFile = numOfPoint *sizeOfPoint / this->sizeOfOutFile;
    divideNPLY(inFile,outFile,numOfFile);
}

void PLYIO::divideNvoxel(string& inFile, string& outFile, size_t voxel_size){
    size_t index_x, index_y;
    loadPLY();
    float* pts_xyz =  (float*) malloc (3 * sizeof(float));
    u_char* pts_rgb = (u_char*) malloc (3 * sizeof(u_char));
    // 利用fstream 进行读写
    for (size_t i = 0; i < this->numOfPoint; i++)
    {
        fread(pts_xyz,sizeof(float),3,file_open);
        fread(pts_rgb,sizeof(u_char),3,file_open);
        
    }
    
}