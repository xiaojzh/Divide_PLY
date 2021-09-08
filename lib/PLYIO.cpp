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
    file_open = fopen(_in_file,"rb");
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
    Point_XYZ *pts = new Point_XYZ[slidSizeOfPoint];
    for (size_t i = 0; i < this->NumOfOutFile; i++)
    {
        // if (i == (this->NumOfOutFile -1))
        // {
            // slidSizeOfPoint = this->numOfPoint - i * slidSizeOfPoint;
        // }
        // Point_XYZ *pts = (Point_XYZ*)malloc(slidSizeOfPoint*sizeof(Point_XYZ));
        fread(pts,sizeof(Point_XYZ),slidSizeOfPoint,file_open);
        char* fileName;
        string fileName1;
        fileName1 = "/home/ouong/SLAM/bag/PLYIO/bag/ShanghaiTech_"+ to_string(i) + ".ply";
        fileName = (char*)fileName1.c_str();
        PLYIO::saveMap(pts,fileName,slidSizeOfPoint);
        // free(pts);
    } 
    delete[] pts; 


    // 最后一个文件
    slidSizeOfPoint = this->numOfPoint - slidSizeOfPoint * this->NumOfOutFile;
    pts = new Point_XYZ[slidSizeOfPoint];
    fread(pts,sizeof(Point_XYZ),slidSizeOfPoint,file_open);
    char* fileName;
    string fileName1;
    fileName1 = "/home/ouong/SLAM/bag/PLYIO/bag/ShanghaiTech_"+ to_string(this->NumOfOutFile) + ".ply";
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
}