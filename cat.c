#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void cat(const char *path)
{
	FILE *fp = strcmp(path, "-") ? fopen(path, "r") : stdin;
	char *buf;
	struct stat fs;
	if (fp) {
		fstat(fileno(fp), &fs);
	} else return;
	if(posix_memalign((void **)&buf, sysconf(_SC_PAGESIZE), fs.st_blksize))
		return;
	if (isatty(fileno(fp))) {
		while (fgets(buf, (int)fs.st_blksize - 1, stdin))
			fputs(buf, stdout);
	} else while (!feof(fp)) 
		fwrite(buf, 1, fread(buf, 1, fs.st_blksize, fp), stdout);
	if (fp == stdin)
		clearerr(fp);
	else fclose(fp);
		
	free(buf);
}

int main(int argc, char *argv[])
{
	int i = 1, errors = 0;
	
	if (argc < 2)
		cat("-");
	else for (i = 1, errors = 0; i < argc; i++) {
		cat(argv[i]);
		if (errno) {
			fprintf(stderr, "%s: %s: %s\n", 
			        argv[0], argv[i], strerror(errno));
			errors++;
		}
	}
	return errors;
}
