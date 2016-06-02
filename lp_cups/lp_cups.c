#include <stdio.h>
#include <cups/cups.h>
#include <string.h>


int main(int argc, char *argv[]) {
	if (argc < 5) {
		printf("Usage: lp_cups printer_name file_name title option1 option2 ... optionN\n");
		return 1;
	}
	char *printer_name = argv[1];
	char *file_name = argv[2];
	char *title = argv[3];
	int len_str_options = 0;
	char *str_options;
	int i;
	for (i = 4;i < argc;i++)
		len_str_options += strlen(argv[i]) + 1;
	str_options = (char *)malloc(sizeof(char) * len_str_options);
	if (str_options == NULL) {
		printf("Error: malloc(%d)", len_str_options);
		return 1;
	}
	char *p = str_options;
	int l;
	for (i = 4;i < argc;i++) {
		strcpy(p, argv[i]);
		l = strlen(argv[i]);
		p[l] = ' ';
		p += l + 1;
	}
	str_options[len_str_options - 1] = '\0';
	//printf("%s\n", str_options);
	cups_option_t *options;
	int num_options = cupsParseOptions(str_options, 0, &options);
	int job_id = cupsPrintFile(printer_name,
								file_name,
								title,
								num_options,
								options);
	//if (job_id == 0)
//		puts(cupsLastErrorString());
	cupsFreeOptions(num_options, options);
	free(str_options);
	printf("%d", job_id);
	return 0;
}
