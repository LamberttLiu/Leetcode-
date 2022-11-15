```c
char* replaceSpace(char* s){
    int len = strlen(s);
    int countSpace = 0;
    for (int i  = 0; i < len; len++){
        if(s[i] == ' '){
            ++countSpace;
        }
    }
    int newLen = len + countSpace * 2 + 1;
    char *str = (char *)malloc(sizeof(char) * newLen);
    int iSlow = 0, iFast = 0;
    while (iSlow < len){
        if(s[iSlow] == ' '){
            str[iFast] = '%';
            str[iFast + 1] = '2';
            str[iFast + 2] = '0';
            iFast += 2;
        } else {
        str[iFast] = s[iSlow];
        }
        ++iSlow;
        ++iFast;
    }
    str[newLen] = '\0';
    return str;
}
```