#include "../include/PLYIO.h"

void writeHeader(char const* filename, size_t numOfPoint);

PLYIO::PLYIO(){
    this->is_in_file_set = false;
    this->numOfOutFile = 10;
    this-> voxel_size = 60;
}

PLYIO::~PLYIO(){
    fclose(file_open);
}

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

void PLYIO::divideNPLY(const string& inFile, const string& outFile, size_t numOfOutFile){
    // 读取文件名称
    this->_in_file = inFile; 
    // 查看是否满足文件名的要求
    if (!(EndWith(_in_file,".ply") || EndWith(_in_file,".PLY")))
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

void PLYIO::divideNsize(const string& inFile, const string& outFile, size_t sizeOfOutFile){
    // 转为n个文件
    this->_in_file = inFile;
    this->sizeOfOutFile = sizeOfOutFile;
    loadPLY();
    fclose(file_open);
    size_t numOfFile = numOfPoint *sizeOfPoint / this->sizeOfOutFile;
    divideNPLY(inFile,outFile,numOfFile);
}

void PLYIO::divideNvoxel(const string& inFile, const string& outFile, size_t voxel_size){
    this->_in_file = inFile;
    this->_out_file = outFile;    
    loadPLY();

    // 分配内存空间
    float* pts_xyz = (float*) malloc (3*sizeof(float));
    u_char* pts_rgb = (u_char*) malloc (3*sizeof(u_char));
    
    int index_x, index_y;    // 根据点的位置，进行分配
    // 记录最大的以及最小的，之后方便添加header
    // int index_x_max = -100000,
        // index_x_min = 100000,
        // index_y_max = -100000,
        // index_y_min = 100000;    // 如果检索的话，x最大值不一定匹配y的最大值
    FILE *fp;
    string fileName;            // 输出文件名，命名原则是根据点云中起始点
    // char line[LENGTH_OF_LINE];
    size_t is_first_open[100*100] = {0};    // 用来检索哪个文件被读写过
    for (size_t i = 0; i < this->numOfPoint; i++)
    {          
        fread(pts_xyz,3,sizeof(float),file_open);
        fread(pts_rgb,3,sizeof(u_char),file_open);
        // 需要考虑点在负坐标轴
        index_x = (pts_xyz[0] < 0) ? (pts_xyz[0] / voxel_size - 1) : (pts_xyz[0] / voxel_size);
        index_y = (pts_xyz[1] < 0) ? (pts_xyz[1] / voxel_size - 1) : (pts_xyz[1] / voxel_size);

        // 记录被打开的输出文件的检索
        int index_file = (index_x + 20)* 100 + (index_y + 20);    // 加5000进行偏移，由于数组的检索不能是小于0的数

        fileName = this->_out_file + "/" + "ShanghaiTech_" + to_string(index_x) + "_" + to_string(index_y) + ".ply";
        if (is_first_open[index_file] != 0)
        {
            if ((fp = fopen(fileName.c_str(), "ab")) == NULL) 
            {
                cout << "Error: cann't open the out files" << endl;
            }
        } 
        else 
        {
            if ((fp = fopen(fileName.c_str(), "wb")) == NULL) 
            {
                cout << "Error: cann't open the out files" << endl;
            }
        }
        fwrite(pts_xyz,3,sizeof(float),fp);
        fwrite(pts_rgb,3,sizeof(u_char),fp);
        fclose(fp);
        is_first_open[index_file] += 1;                     // 用于记录这个voxel中的点的个数
        // 所以依然选择利用一个检索文件进行维护输出文件列表，这样方便后面添加header
        // bool is_first_open = true;
        // char line[LENGTH_OF_LINE];
        // FILE* index_fp;
        // string index_file = _out_file + "/indexOutFile.dat";
        // if ((index_fp = fopen(index_file.c_str(),"ab+"))==NULL)
        // {
            // cout << "Error: cann't open the index file" << endl;
        // }
        // while (fgets(line,LENGTH_OF_LINE,index_fp))
        // {
            // if (strstr(line,fileName.c_str()) != NULL)
            // {
                // is_first_open = false;
                // break;
            // }
        // } // 用一个数组进行维护，index[x*100+y] = 1,表示存在这个文件，再进行解码
    }
    delete[] pts_xyz;
    delete[] pts_rgb;

    // for (int i = 0; i < 100*100; i++)   // i 使用uchar类型会导致后面计算出现强制类型转换
    // {
    //     if (is_first_open[i] == 0)
    //     {
    //         continue;
    //     }
    //     int _index_x = i / 100 - 20;
    //     int _index_y = i % 100 - 20;
    //     string _index_fileName  = this->_out_file + "/" + "ShanghaiTech_" 
    //                             + to_string(_index_x) + "_" + to_string(_index_y) + ".ply";
    //     size_t numOfPoint = is_first_open[i];
    //     writeHeader(_index_fileName.c_str(),numOfPoint);
    // }
    writeHeader(_out_file);
}

// void writeHeader(char const* filename, size_t numOfPoint){
//     int elementNum = numOfPoint;    // 点的个数
//     FILE *fp;
//     if ((fp = fopen(filename, "ab")) == NULL) 
//     {
//         cout << "Error: cann't open the out files" << endl;
//     }
//     // rewind(fp);     // 将写指针回到开头 貌似没有起到作用
//     fseek(fp, 0, SEEK_SET);  // 对于读取有用，写的话只能新建一个，然后添加新的内容，再写上原内容，最后改名
//     fprintf(fp,"ply\n");
//     fprintf(fp, "format binary_little_endian 1.0\n");
// 	fprintf(fp, "comment File generated v1.0 (xiaojzh)\n");
// 	fprintf(fp, "element vertex %d\n", elementNum);
// 	fprintf(fp, "property float x\n");
// 	fprintf(fp, "property float y\n");
// 	fprintf(fp, "property float z\n");
//     fprintf(fp, "property uchar red\n");
//     fprintf(fp, "property uchar green\n");
//     fprintf(fp, "property uchar blue\n");
// 	fprintf(fp, "end_header\n");
//     fclose(fp);
// }

void PLYIO::writeHeader(string dirpath){
    // 首先获取当前文件夹下的文件名
    // 再计算每一个文件的大小，字节数除以15就是点数
    // 新建一个新文件，添加header，并且将原文件内容复制到后面
    DIR* dir = opendir(dirpath.c_str());
    if (dir == NULL)
    {
        cout << "Error: cann't open the dir" << endl;
    }

    vector<string> allPath;
    // vector<size_t> sizeOffile;
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        //cout << "name = " << entry->d_name << ", len = " << entry->d_reclen << ", entry->d_type = " << (int)entry->d_type << endl;
        string name = entry->d_name;
        string imgdir = dirpath +"/"+ name;
        //sprintf("%s",imgdir.c_str());
        allPath.push_back(imgdir);
        // sizeOffile.push_back(entry->d_reclen); 这个获取的是文件名的长度
    }
    closedir(dir);  

    FILE *fp, *tmp_fp;
    string fileName, tmpFileName = dirpath + "/tmp.ply";
    struct stat statbuf;
    size_t sizeOfFile, elementNum;
    for (size_t i = 0; i < allPath.size(); i++)
    {
        fileName = allPath[i];
        stat(fileName.c_str(),&statbuf);
        sizeOfFile = statbuf.st_size;
        elementNum = sizeOfFile / sizeOfPoint;       // 每一个点占据15byte
        // 如果点的数量过少，就不考虑
        if (elementNum < 1000)
        {
            continue;
        }

        if ((tmp_fp = fopen(tmpFileName.c_str(), "wb")) == NULL) 
        {
            cout << "Error: cann't open the tmp out files" << endl;
        }
        fprintf(tmp_fp,"ply\n");
        fprintf(tmp_fp, "format binary_little_endian 1.0\n");
        fprintf(tmp_fp, "comment File generated v1.0 (xiaojzh)\n");
        fprintf(tmp_fp, "element vertex %ld\n", elementNum);
        fprintf(tmp_fp, "property float x\n");
        fprintf(tmp_fp, "property float y\n");
        fprintf(tmp_fp, "property float z\n");
        fprintf(tmp_fp, "property uchar red\n");
        fprintf(tmp_fp, "property uchar green\n");
        fprintf(tmp_fp, "property uchar blue\n");
        fprintf(tmp_fp, "end_header\n");
        if ((fp = fopen(fileName.c_str(),"rb")) == NULL)
        {
            cout << "Error: cann't open the" << fileName << "files" << endl;
        }
        Point_XYZ* pts = (Point_XYZ*)malloc(elementNum*sizeOfPoint);
        fread(pts,sizeOfPoint,elementNum,fp);
        fwrite(pts,sizeOfPoint,elementNum,tmp_fp);
        fclose(fp);
        fclose(tmp_fp);
        // 删除原来的文件，并且给现在的文件改名
        remove(fileName.c_str());
        rename(tmpFileName.c_str(),fileName.c_str());
    }
}