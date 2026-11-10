#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

/*
 * linux : /
 * Windows : \
 */
void dig(const char* path, int depth){
    struct dirent *dp;
    struct stat st;
    DIR* dir;

    if((dir = opendir(path)) == NULL){
        perror("opendir");
        return;
    }

    while((dp = readdir(dir)) != NULL){
        char* name = dp->d_name; // current directory's all files
        char sub_path[255];
        int TYPE = dp->d_type;
        snprintf(sub_path, sizeof(sub_path), "%s/%s", path, name);

        if(strcmp(name, ".") == 0 || strcmp(name, "..") == 0)
            continue;

        if(TYPE == DT_DIR || TYPE == DT_REG)
            for(int i = 0; i < depth; i++)  printf("  ");

        switch(TYPE){
            case DT_DIR:{
                printf("[DIR]%s\n",name);
                dig(sub_path, depth+1);
                break;
            }
            case DT_REG:{
                printf("[FILE]%s\n",name);
                break;
            }
        }
    }
    closedir(dir);
}

int main(int argc, const char* argv[]){
    const char* path = (argc > 1) ? argv[1] : "."; // default directory
    dig(path, 0);
    return 0;
}
