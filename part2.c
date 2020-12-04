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

void passportvalue(char raw[], char key[], char* value)
{
    char tmp[16];
    int i = (int)(strstr(raw, key) -  raw) + strlen(key); int n = 0;
    while (raw[i] != ' ' && raw[i] != '\n')
    {
        tmp[n] = raw[i];
        n++; i++;
    }
    tmp[n] = '\0';
    strcpy(value, tmp);
}

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
    if (strstr(raw, "byr:"))
    {
        char value[16];
        passportvalue(raw, "byr:", &value);

        pass->byr = (1920 <= atoi(value)) &&
                    (2002 >= atoi(value));
    }
    if (strstr(raw, "iyr:"))
    {
        char value[16];
        passportvalue(raw, "iyr:", &value);

        pass->iyr = (2010 <= atoi(value)) &&
                    (2020 >= atoi(value));
    }
    if (strstr(raw, "eyr:"))
    {
        char value[16];
        passportvalue(raw, "eyr:", &value);

        pass->eyr = (2020 <= atoi(value)) &&
                    (2030 >= atoi(value));
    }
    if (strstr(raw, "hgt:"))
    {
        char value[16];
        passportvalue(raw, "hgt:", &value);

        if (strstr(value, "cm"))
        {
            char sub[4];
            strncpy(sub, value, 3);
            pass->hgt = (150 <= atoi(sub)) &&
                        (193 >= atoi(sub));
        } else {
            char sub[3];
            strncpy(sub, value, 2);
            pass->hgt = (59 <= atoi(sub)) &&
                        (76 >= atoi(sub));
        }
    }
    if (strstr(raw, "hcl:"))
    {
        char value[16];
        passportvalue(raw, "hcl:", &value);

        if (value[0] == '#')
        {
            for (size_t i = 0; i < 6; i++)
            {
                if (!strchr("0123456789abcdefgh", value[i + 1])) { break; }
                if (i == 5) { pass->hcl = 1; }
            }
        }
    }
    if (strstr(raw, "ecl:"))
    {
        char value[16];
        passportvalue(raw, "ecl:", &value);

        pass->ecl = (!strcmp("amb", value)) ||
                    (!strcmp("blu", value)) ||
                    (!strcmp("brn", value)) ||
                    (!strcmp("gry", value)) ||
                    (!strcmp("grn", value)) ||
                    (!strcmp("hzl", value)) ||
                    (!strcmp("oth", value));
    }
    if (strstr(raw, "pid:"))
    {
        char value[16];
        passportvalue(raw, "pid:", &value);

        pass->pid = (0 != atoi(value)) &&
                    (9 == strlen(value));
    }
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
