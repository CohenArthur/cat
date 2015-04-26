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
	int errbuf = errno, fd = fileno(fp);
	struct stat fs;
	if (!fp)
		return 1;
	fstat(fd, &fs);
	size_t buflen = 16 * fs.st_blksize;
	if (posix_memalign((void **)&buf, sysconf(_SC_PAGESIZE), buflen))
		return 1;
	if (isatty(fd)) { /* line-buffer if tty */
		while (fgets(buf, (int)buflen - 1, stdin))
			fputs(buf, stdout);
	} else {
		errno = errbuf; /* isatty always sets errno on false... */
		while (read(fd, buf, buflen)) 
			write(fileno(stdout), buf, buflen);
	}
	if (fp == stdin) clearerr(fp);
	else fclose(fp); /* we want stdin open for multiple reads */		
	free(buf);
	return 0;
}

int main(int argc, char *argv[])
{
	int i = 0, errors = 0;
	
	if (argc < 2)
		return cat("-");
	while (++i < argc) if (cat(argv[i])) {
		fprintf(stderr, "%s: %s: %s\n", argv[0], argv[i], strerror(errno));
		errors++;
	}
	return errors;
}
