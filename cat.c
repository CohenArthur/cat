#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int cat(const char *path)
{
	FILE *fp = strcmp(path, "-") ? fopen(path, "r") : stdin;
	char *buf;
	struct stat fs;
	if (!fp)
		return 1;
	fstat(fileno(fp), &fs);
	if (posix_memalign((void **)&buf, sysconf(_SC_PAGESIZE), fs.st_blksize))
		return 1;
	if (errno = isatty(fileno(fp)) ? errno : 0) {
		while (fgets(buf, (int)fs.st_blksize - 1, stdin))
			fputs(buf, stdout);
	} else while (!feof(fp)) 
		fwrite(buf, 1, fread(buf, 1, fs.st_blksize, fp), stdout);
	if (fp == stdin) clearerr(fp);
	else fclose(fp);
		
	free(buf);
	return 0;
}

int main(int argc, char *argv[])
{
	int i = 0, errors = 0;
	
	if (argc < 2)
		return cat("-");
	while (++i < argc) {
		errors += cat(argv[i]);
		if (errno)
			fprintf(stderr, "%s: %s: %s\n", 
			        argv[0], argv[i], strerror(errno));
	}
	return errors;
}
