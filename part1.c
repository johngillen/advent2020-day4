#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
    int byr;
    int iyr;
    int eyr;
    int hgt;
    int hcl;
    int ecl;
    int pid;
    int cid;
    int valid;
} passport;

void validatepassport(passport* pass)
{
    pass->valid = pass->byr &&
                  pass->iyr &&
                  pass->eyr &&
                  pass->hgt &&
                  pass->hcl &&
                  pass->ecl &&
//                  pass->cid &&
                  pass->pid;
}

void checkpassport(char raw[], passport* pass)
{
    if (strstr(raw, "byr:")) { pass->byr = 1; }
    if (strstr(raw, "iyr:")) { pass->iyr = 1; }
    if (strstr(raw, "eyr:")) { pass->eyr = 1; }
    if (strstr(raw, "hgt:")) { pass->hgt = 1; }
    if (strstr(raw, "hcl:")) { pass->hcl = 1; }
    if (strstr(raw, "ecl:")) { pass->ecl = 1; }
    if (strstr(raw, "pid:")) { pass->pid = 1; }
    if (strstr(raw, "cid:")) { pass->cid = 1; }
}

void resetpassport(passport* pass) {
    pass->byr = 0;
    pass->iyr = 0;
    pass->eyr = 0;
    pass->hgt = 0;
    pass->hcl = 0;
    pass->ecl = 0;
    pass->pid = 0;
    pass->cid = 0;
    pass->valid = 0;
}

int main(int argc, char const *argv[])
{
    FILE * file;
    file = fopen("input", "r");

    char buffer[1096];
    passport pass = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    int validpass = 0;

    while (fgets(buffer, 1095, file))
    {
        if (strlen(buffer) > 2)
        {
            checkpassport(buffer, &pass);

        } else {
            validatepassport(&pass);
            if (pass.valid) { validpass++; }
            resetpassport(&pass);
        }
    }
    
    validatepassport(&pass);
    if (pass.valid) { validpass++; }
    
    printf("\"valid\" passports: %d\n", validpass);

    return 0;
}
