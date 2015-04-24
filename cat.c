#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int cat(const char *path)
{
	if (!strcmp("-", path)) {
		for (int c; (c = getchar()) != EOF; putchar(c));
	} else {
		FILE *fp;
		if (!(fp = fopen(path, "r"))) {
			fprintf(stderr, "cat: %s: %s\n", path, strerror(errno));
		} else {
			struct stat fs;
			stat(path, &fs);
			size_t ps = sysconf(_SC_PAGESIZE);
			char *buf = malloc(fs.st_blksize + ps - 1);
			uintptr_t start = (uintptr_t) buf;
			char *pg = (char *) (start + ps - start % ps);
			while (!feof(fp)) 
				fwrite(pg, 1, fread(pg, 1, fs.st_blksize, fp), stdout);
			fclose(fp);
			free(buf);
		}
	}
	return !!errno;
}

int main(int argc, char *argv[])
{
	int i = 1, errors = 0;
	if (argc < 2)
		cat("-");
	else
		while (i < argc) errors += cat(argv[i++]);
	return errors;
}
