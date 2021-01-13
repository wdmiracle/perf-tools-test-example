#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

#include <string.h>


#define	FILE_PATH "./test.txt"
#define	BUF	"Test for perf tool	"

#define FILE_SIZE	10*1024*1024

#define	DELETE_FILE	0

/*
 * Test for perf-tools
*/
int main(int argc, int *argv[])
{
	int fd = 0;
	int ret = -1;
	struct stat stat_buf;

	/*
	 * int open(const char *pathname, int flags, mode_t mode);
	 * @flags : file creation flags
	 * @mode : access mode
	 *  flags and mode, need to be consistent.
	*/
	fd = open(FILE_PATH, O_CREAT|O_RDWR|O_TRUNC, S_IRWXU|S_IRWXG|S_IRWXO);
	if (fd < 0){
		printf("open %s failed(%s) ...\n", FILE_PATH, strerror(errno));
		return errno;
	}

//	printf("sizeof BUF %d\n", sizeof(BUF));

	while (1) {
		ret = write(fd, BUF, sizeof(BUF));
		if (ret < 0) {
			printf("write %s failed(%s) ... \n", FILE_PATH, strerror(errno));
			close(fd);
			return errno;
		}

		ret = stat(FILE_PATH, &stat_buf);
		if (ret < 0) {
			printf("stat %s failed... \n", FILE_PATH);
			close(fd);
			return errno;
		}
		printf("write file: %s size : %d\n", FILE_PATH, (int)stat_buf.st_size);

		if (stat_buf.st_size == FILE_SIZE) {
			printf("write file: %s size : %d\n", FILE_PATH, (int)stat_buf.st_size);
			break;
		}
	}


	close(fd);
#if DELETE_FILE
	ret = unlink(FILE_PATH);
	if (ret < 0) {
		printf("Delete file : %s failed\n", FILE_PATH);
	}
	printf("\n Test end, delete file %s\n", FILE_PATH);
#endif

	return 0;
}
