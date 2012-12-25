#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main (int argc, char* argv[])
{
	FILE *fpin, *fpout;
	int8_t tempIoBuf[2];
	int8_t buf[2];
	int16_t numRead, numWrite;
	int16_t i;

	if (argc < 3) {
		printf ("usage le2be infile outfile \n"); 		
		exit (0);
	}

	/*Following Code checks the machine type*/
	int num = 1;
	if(*(char *)&num == 1)
	{
		printf("Little-Endian\n");
	}
	else
	{
		printf("Big-Endian\n");
	} 

	fpin = fopen (argv[1], "rb");
	if (fpin == NULL) {
		perror ("input file Not found");
		goto exit;
	}

	fpout = fopen (argv[2], "wb");
	if (fpout == NULL) {
		perror ("Not able to open the output file");
		goto exit;
	}

	while (!feof (fpin)){
		/* read the file*/
		numRead = fread(&tempIoBuf, sizeof(int8_t), 2, fpin);
		/* check for endo of file */
		if ( numRead != 2 )
		{
			break;
		}
		/* pack bytes into words */
		for (i = 0; i < 2; i++)
		{
			buf[0]  = tempIoBuf[1];
			buf[1]  = tempIoBuf[0];
		}
		numWrite = fwrite(&buf, sizeof(int8_t), 2, fpout);
		/* check for endo of file */
		if ( numWrite != 2 )
		{
			break;
		}
	}

exit:
	if (fpin != NULL) fclose (fpin);
	if (fpout != NULL) fclose (fpout);

	return 0;
}
