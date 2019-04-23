#include "omex.h"


void readOMEX(char *OMEXfilename, char *filename, char *model_sbml)
{
    std::cout << "Hello from omex" << std::endl;

    int error(0);
    zip *foo = zip_open(OMEXfilename, 0, &error);
    std::cout << "Success" << std::endl;

    int files_total = zip_get_num_entries(foo, 0);
    printf("Note: we have only %d files in ZIP\n",files_total);


    struct zip_stat sb;
    int r, len;
    long long sum;
    char buffer[10000];

    for (int i = 0; i < zip_get_num_entries(foo, 0); i++) {
        if (zip_stat_index(foo, i, 0, &sb) == 0) {
            printf("==================\n");
            printf("Name: [%s], ", sb.name);
            printf("Size: [%llu], ", sb.size);
            printf("Index: [%llu], ", sb.index);
            printf("Valid: [%llu], ", sb.valid);
            printf("mtime: [%u]\n", (unsigned int) sb.mtime);

            if (strcmp(filename, sb.name) == 0) {

                zip_file *zf = zip_fopen_index(foo, i, 0);
                if (!zf) {
                    fprintf(stderr, "boese, boese\n");
                    std::cout << "failed to opne  entry of archive. " << zip_strerror(foo) << std::endl;
                    zip_close(foo);
                }

                sum = 0;
                while (sum != sb.size) {
                    len = zip_fread(zf, buffer, 100);
                    if (len < 0) {
                        fprintf(stderr, "boese, boese\n");
                        exit(102);
                    }
                    printf("%s", buffer, len);
                    sum += len;
                }
                zip_fclose(zf);
                printf("==================\n");
            }
            std::cout<<std::endl;
        }
    }
}

char *readfile(std::string filename, size_t *size) {
    char * buffer;
    size_t result;

    FILE* pFile = fopen (filename.c_str(), "rb" );
    if (pFile==NULL) {fputs ("File error",stderr); exit (1);}

    // obtain file size:
    fseek (pFile , 0 , SEEK_END);
    unsigned int lSize = ftell (pFile);
    rewind (pFile);

    // allocate memory to contain the whole file:
    buffer = (char*) malloc (sizeof(char)*lSize);
    if (buffer == NULL) {fputs ("Memory error",stderr); exit (2);}

    // copy the file into the buffer:
    result = fread (buffer,1,lSize,pFile);
    if (result != lSize) {fputs ("Reading error",stderr); exit (3);}

    /* the whole file is now loaded in the memory buffer. */

    // terminate
    fclose (pFile);
    *size = lSize;
    return buffer;

}
zip * get_archive(std::string path, int flags) {
    int error = 0;
    zip *archive = zip_open(path.c_str(), flags , &error);

    if(!archive) {
        std::cout << "could not open or create archive" <<  path << std::endl;
        exit(1) ;
    }
    std::cout << "Done : creating archieve" << path <<  std::endl;
    return archive;
}

void addOMEX(char* path, char* filename) {

    int error = 0;
    zip *archive = zip_open(path, ZIP_CREATE, &error);

    if(error)
    {
        std::cout << "could not open or create archive" << std::endl;
    }

    int index;
    size_t len;
    char *data = readfile(filename, &len);
    //std::cout << "File content \n" << "Name " << filename << "\nSize " << len << "\n" << data << std::endl;

    zip_source *source = zip_source_buffer(archive, data, len, 0);
    if (source == NULL) {
        std::cout << "failed to create source buffer. " << zip_strerror(archive) << std::endl;
        return;
    }

    index = (int)zip_file_add(archive, filename, source, ZIP_FL_ENC_UTF_8);
    //index = (int) zip_add(archive, filename, source);
    if (index < 0) {
        zip_source_free(source);
        std::cout << "failed to add file to archive. " << zip_strerror(archive) << std::endl;
        return;
    }
    zip_close(archive);
}