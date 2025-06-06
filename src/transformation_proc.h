
//Emmanuel Torres
//Tecnologico de Monterrey
//Campus Puebla
//Octubre 2024
extern void itoa2(int N, char *str) {
    int i = 0;

    // Save the copy of the number for sign
    int sign = N;

    // If the number is negative, make it positive
    if (N < 0)
        N = -N;

    // Extract digits from the number and add them to the
    // string
    while (N > 0) {
        // Convert integer digit to character and store
        // it in the str
        str[i++] = N % 10 + '0';
        N /= 10;
    }

    // If the number was negative, add a minus sign to the
    // string
    if (sign < 0) {
        str[i++] = '-';
    }

    // Null-terminate the string
    str[i] = '\0';

    // Reverse the string to get the correct order
    for (int j = 0, k = i - 1; j < k; j++, k--) {
        char temp = str[j];
        str[j] = str[k];
        str[k] = temp;
    }
}

extern void gray_img(char mask[10], char path[80], const char *output_dir, int *leidas, int *escritas) {
    FILE *image, *outputImage;
    char output_path[256];
    snprintf(output_path, sizeof(output_path), "%s/%s.bmp", output_dir, mask);

    image = fopen(path,"rb");          //Original Image
    outputImage = fopen(output_path,"wb");

    if (image == NULL) {
        fprintf(stderr, "Error: No pudo abrir imagen de input en %s\n", path);
        return;
    }
    if (outputImage == NULL) {
        fprintf(stderr, "Error: No pudo crear imagen de output %s\n", output_path);
        fclose(image);
        return;
    }

    //Definition of variables
    int i;
    long ancho, alto;
    unsigned char r, g, b, pixel;               //Pixel

    unsigned char xx[54];
    fread(xx, sizeof(unsigned char), 54, image);
    fwrite(xx, sizeof(unsigned char), 54, outputImage);

    ancho = (long)xx[20]*65536+(long)xx[19]*256+(long)xx[18];
    alto = (long)xx[24]*65536+(long)xx[23]*256+(long)xx[22];

    int tam = ancho * alto;

    unsigned char *arr_in = (unsigned char*)malloc(tam * 3);
    unsigned char *arr_out = (unsigned char*)malloc(tam * 3);

    if (arr_in == NULL || arr_out == NULL) {
        fprintf(stderr, "Fallo en malloc gray_img.\n");
        fclose(image);
        fclose(outputImage);
        free(arr_in);
        free(arr_out);
        return;
    }

    fread(arr_in, sizeof(unsigned char), tam * 3, image);
    *leidas = tam * 3;

    for (i = 0; i < ancho * alto; i++) {
        r = arr_in[i * 3 + 2];
        g = arr_in[i * 3 + 1];
        b = arr_in[i * 3 + 0];
        pixel = 0.21 * r + 0.72 * g + 0.07 * b;
        arr_out[i * 3 + 0] = pixel;
        arr_out[i * 3 + 1] = pixel;
        arr_out[i * 3 + 2] = pixel;
    }

    fwrite(arr_out, sizeof(unsigned char), tam * 3, outputImage);
    *escritas = tam * 3;

    free(arr_in);
    free(arr_out);

    fclose(image);
    fclose(outputImage);
}

extern void invH_gray_img(char mask[10], char path[80], const char *output_dir, int *leidas, int *escritas) {
    FILE *image, *outputImage;
    char output_path[256];
    snprintf(output_path, sizeof(output_path), "%s/%s.bmp", output_dir, mask);


    image = fopen(path,"rb");          //Original Image
    outputImage = fopen(output_path,"wb");


    if (image == NULL) {
        fprintf(stderr, "Error: Could not open input image at %s\n", path);
        return;
    }
    if (outputImage == NULL) {
        fprintf(stderr, "Error: Could not create output image at %s\n", output_path);
        fclose(image);
        return;
    }


    //Definition of variables
    int i, j;
    long ancho, alto;
    unsigned char r, g, b, pixel;               //Pixel


    unsigned char xx[54];
    fread(xx, sizeof(unsigned char), 54, image);
    fwrite(xx, sizeof(unsigned char), 54, outputImage);


    ancho = (long)xx[20]*65536+(long)xx[19]*256+(long)xx[18];
    alto = (long)xx[24]*65536+(long)xx[23]*256+(long)xx[22];


    int padding = (4 - (ancho * 3) % 4) % 4;
    int tam = ancho * alto;


    unsigned char *arr_in = (unsigned char*)malloc(tam * 3);
    unsigned char *arr_out = (unsigned char*)malloc(tam * 3);


    if (arr_in == NULL || arr_out == NULL) {
        fprintf(stderr, "Memory allocation failed in invH_gray_img.\n");
        fclose(image);
        fclose(outputImage);
        return;
    }
   
    fread(arr_in, sizeof(unsigned char), tam * 3, image);
    *leidas = tam * 3;
   
    for (i = 0; i < ancho * alto; i++) {
        r = arr_in[i * 3 + 2];
        g = arr_in[i * 3 + 1];
        b = arr_in[i * 3 + 0];
        pixel = 0.21 * r + 0.72 * g + 0.07 * b;
        arr_out[i] = pixel;
    }


    for (i = 0; i < alto; i++) {
        for (j = ancho; j > 0; j--) {
            int index = (i * ancho) + j;
            fputc(arr_out[index], outputImage);
            fputc(arr_out[index], outputImage);
            fputc(arr_out[index], outputImage);
        }
        for (int p = 0; p < padding; p++) {
            fputc(0x00, outputImage);
        }
    }
    *escritas = tam * 3;


    free(arr_in);
    free(arr_out);


    fclose(image);
    fclose(outputImage);


}


extern void invV_gray_img(char mask[10], char path[80], const char *output_dir, int *leidas, int *escritas) {
    FILE *image, *outputImage;
    char output_path[256];
    snprintf(output_path, sizeof(output_path), "%s/%s.bmp", output_dir, mask);


    image = fopen(path,"rb");          //Original Image
    outputImage = fopen(output_path,"wb");


    if (image == NULL) {
        fprintf(stderr, "Error: Could not open input image at %s\n", path);
        return;
    }
    if (outputImage == NULL) {
        fprintf(stderr, "Error: Could not create output image at %s\n", output_path);
        fclose(image);
        return;
    }


    //Definition of variables
    int i, j;
    long ancho, alto;
    unsigned char r, g, b, pixel;               //Pixel


    unsigned char xx[54];
    fread(xx, sizeof(unsigned char), 54, image);
    fwrite(xx, sizeof(unsigned char), 54, outputImage);


    ancho = (long)xx[20]*65536+(long)xx[19]*256+(long)xx[18];
    alto = (long)xx[24]*65536+(long)xx[23]*256+(long)xx[22];


    int padding = (4 - (ancho * 3) % 4) % 4;
    int tam = ancho * alto;


    unsigned char *arr_in = (unsigned char*)malloc(tam * 3);
    unsigned char *arr_out = (unsigned char*)malloc(tam * 3);


    if (arr_in == NULL || arr_out == NULL) {
        fprintf(stderr, "Memory allocation failed in invV_gray_img.\n");
        fclose(image);
        fclose(outputImage);
        return;
    }
   
    fread(arr_in, sizeof(unsigned char), tam * 3, image);
    *leidas = tam * 3;
   
    for (i = 0; i < ancho*alto; i++) {
        r = arr_in[i * 3 + 2];
        g = arr_in[i * 3 + 1];
        b = arr_in[i * 3 + 0];
        pixel = 0.21 * r + 0.72 * g + 0.07 * b;
        arr_out[i] = pixel;
    }


    for (i = alto - 1; i > 0; i--) {
        for (j = 0; j < ancho; j++) {
            int index = (i * ancho) + j;
            fputc(arr_out[index], outputImage);
            fputc(arr_out[index], outputImage);
            fputc(arr_out[index], outputImage);
        }
        for (int p = 0; p < padding; p++) {
            fputc(0x00, outputImage);
        }
    }
    *escritas = tam * 3;


    free(arr_in);
    free(arr_out);


    fclose(image);
    fclose(outputImage);


}


extern void invH_color_img(char mask[10], char path[80], const char *output_dir, int *leidas, int *escritas) {
    FILE *image, *outputImage;
    char output_path[256];
    snprintf(output_path, sizeof(output_path), "%s/%s.bmp", output_dir, mask);


    image = fopen(path,"rb");          //Original Image
    outputImage = fopen(output_path,"wb");


    if (image == NULL) {
        fprintf(stderr, "Error: Could not open input image at %s\n", path);
        return;
    }
    if (outputImage == NULL) {
        fprintf(stderr, "Error: Could not create output image at %s\n", output_path);
        fclose(image);
        return;
    }


    //Definition of variables
    int i, j, k;
    long ancho, alto;
    unsigned char r, g, b, pixel;               //Pixel


    unsigned char xx[54];
    fread(xx, sizeof(unsigned char), 54, image);
    fwrite(xx, sizeof(unsigned char), 54, outputImage);


    ancho = (long)xx[20]*65536+(long)xx[19]*256+(long)xx[18];
    alto = (long)xx[24]*65536+(long)xx[23]*256+(long)xx[22];


    int padding = (4 - (ancho * 3) % 4) % 4;
    int tam = ancho * alto;


    unsigned char *arr_in_b = (unsigned char*)malloc(tam);
    unsigned char *arr_in_g = (unsigned char*)malloc(tam);
    unsigned char *arr_in_r = (unsigned char*)malloc(tam);


    if (arr_in_b == NULL || arr_in_g == NULL || arr_in_r == NULL) {
        fprintf(stderr, "Memory allocation failed in invH_color_img.\n");
        fclose(image);
        fclose(outputImage);
        return;
    }
   
    for (int i = 0; i < alto; i++) {
        for (int j = 0; j < ancho; j++) {
            b = fgetc(image);
            g = fgetc(image);
            r = fgetc(image);


            int index = (i * ancho) + j;
            arr_in_b[index] = b;
            arr_in_g[index] = g;
            arr_in_r[index] = r;
        }
        fseek(image, padding, SEEK_CUR);
    }
    *leidas = tam * 3;


    for (i = 0; i < alto; i++) {
        for (k = ancho; k > 0; k--) {
            int index = (i * ancho) + k;
            fputc(arr_in_b[index], outputImage);
            fputc(arr_in_g[index], outputImage);
            fputc(arr_in_r[index], outputImage);
        }
        for (int p = 0; p < padding; p++) {
            fputc(0x00, outputImage);
        }
    }
    *escritas = tam * 3;


    free(arr_in_b);
    free(arr_in_g);
    free(arr_in_r);


    fclose(image);
    fclose(outputImage);


}


extern void invV_color_img(char mask[10], char path[80], const char *output_dir, int *leidas, int *escritas) {
    FILE *image, *outputImage;
    char output_path[256];
    snprintf(output_path, sizeof(output_path), "%s/%s.bmp", output_dir, mask);


    image = fopen(path,"rb");          //Original Image
    outputImage = fopen(output_path,"wb");


    if (image == NULL) {
        fprintf(stderr, "Error: Could not open input image at %s\n", path);
        return;
    }
    if (outputImage == NULL) {
        fprintf(stderr, "Error: Could not create output image at %s\n", output_path);
        fclose(image);
        return;
    }


    //Definition of variables
    int i, j, k;
    long ancho, alto;
    unsigned char r, g, b, pixel;               //Pixel


    unsigned char xx[54];
    fread(xx, sizeof(unsigned char), 54, image);
    fwrite(xx, sizeof(unsigned char), 54, outputImage);


    ancho = (long)xx[20]*65536+(long)xx[19]*256+(long)xx[18];
    alto = (long)xx[24]*65536+(long)xx[23]*256+(long)xx[22];


    int padding = (4 - (ancho * 3) % 4) % 4;
    int tam = ancho * alto;


    unsigned char *arr_in_b = (unsigned char*)malloc(tam);
    unsigned char *arr_in_g = (unsigned char*)malloc(tam);
    unsigned char *arr_in_r = (unsigned char*)malloc(tam);


    if (arr_in_b == NULL || arr_in_g == NULL || arr_in_r == NULL) {
        fprintf(stderr, "Memory allocation failed in invV_color_img.\n");
        fclose(image);
        fclose(outputImage);
        return;
    }


    for (int i = 0; i < alto; i++) {
        for (int j = 0; j < ancho; j++) {
            b = fgetc(image);
            g = fgetc(image);
            r = fgetc(image);


            int index = (i * ancho) + j;
            arr_in_b[index] = b;
            arr_in_g[index] = g;
            arr_in_r[index] = r;
        }
        fseek(image, padding, SEEK_CUR);
    }
    *leidas = tam * 3;




    for (i = alto - 1; i > 0; i--) {
        for (k = 0; k < ancho; k++) {
            int index = (i * ancho) + k;
            fputc(arr_in_b[index], outputImage);
            fputc(arr_in_g[index], outputImage);
            fputc(arr_in_r[index], outputImage);
        }
        for (int p = 0; p < padding; p++) {
            fputc(0x00, outputImage);
        }
    }
    *escritas = tam * 3;


    free(arr_in_b);
    free(arr_in_g);
    free(arr_in_r);


    fclose(image);
    fclose(outputImage);


}






extern void blur_img(char mask[10], char path[80], int kernel, const char *output_dir, int *leidas, int *escritas) {
    FILE *image, *outputImage;
    char output_path[256];
    snprintf(output_path, sizeof(output_path), "%s/%s.bmp", output_dir, mask);

    image = fopen(path,"rb");
    outputImage = fopen(output_path,"wb");

    if (image == NULL) {
        fprintf(stderr, "Error: No pudo abrir imagen de input en %s\n", path);
        return;
    }
    if (outputImage == NULL) {
        fprintf(stderr, "Error: No pudo crear imagen de output %s\n", output_path);
        fclose(image);
        return;
    }

    int i, j, k;
    long ancho, alto;
    unsigned char r, g, b, pixel;

    unsigned char xx[54];
    fread(xx, sizeof(unsigned char), 54, image);
    fwrite(xx, sizeof(unsigned char), 54, outputImage);

    ancho = (long)xx[20]*65536+(long)xx[19]*256+(long)xx[18];
    alto = (long)xx[24]*65536+(long)xx[23]*256+(long)xx[22];

    int padding = (4 - (ancho * 3) % 4) % 4;
    int row_size_padded = (ancho * 3) + padding;
    int tam_pixels = ancho * alto;
    int tam_bytes = alto * row_size_padded;

    unsigned char *arr_in = (unsigned char*)malloc(tam_pixels * 3);
    unsigned char *arr_temp = (unsigned char*)malloc(tam_pixels * 3);
    unsigned char *arr_out = (unsigned char*)malloc(tam_pixels * 3);

    if (arr_in == NULL || arr_temp == NULL || arr_out == NULL) {
        fprintf(stderr, "Fallo en malloc blur_img.\n");
        fclose(image);
        fclose(outputImage);
        free(arr_in);
        free(arr_temp);
        free(arr_out);
        return;
    }

    fseek(image, 54, SEEK_SET);
    for (int i = 0; i < alto; i++) {
        fread(arr_in + (i * ancho * 3), sizeof(unsigned char), ancho * 3, image);
        fseek(image, padding, SEEK_CUR);
    }
    *leidas = (tam_pixels * 3) + (kernel * kernel) - 1;

    if (kernel < 1 || kernel % 2 == 0) {
        fprintf(stderr, "Error: El kernel debe ser impar y mayor que cero.\n");
        free(arr_in);
        free(arr_temp);
        free(arr_out);
        fclose(image);
        fclose(outputImage);
        return;
    }

    int kernelRadius = (kernel - 1) / 2;

    for (int y = 0; y < alto; y++) {
        for (int x = 0; x < ancho; x++) {
            long bSum = 0, gSum = 0, rSum = 0;
            int count = 0;

            for (int kx = -kernelRadius; kx <= kernelRadius; kx++) {
                int nx = x + kx;
                if (nx >= 0 && nx < ancho) {
                    int index =( y * ancho + nx) * 3;
                    bSum += arr_in[index + 0];
                    gSum += arr_in[index + 1];
                    rSum += arr_in[index + 2];
                    count++;
                }
            }

            int index = (y * ancho + x) * 3;
            arr_temp[index + 0] = (unsigned char)((count > 0) ? (bSum / count) : 0);
            arr_temp[index + 1] = (unsigned char)((count > 0) ? (gSum / count) : 0);
            arr_temp[index + 2] = (unsigned char)((count > 0) ? (rSum / count) : 0);
        }
    }

    for (int y = 0; y < alto; y++) {
        for (int x = 0; x < ancho; x++) {
            long bSum = 0, gSum = 0, rSum = 0;
            int count = 0;

            for (int ky = -kernelRadius; ky <= kernelRadius; ky++) {
                int ny = y + ky;
                if (ny >= 0 && ny < alto) {
                    int index = (ny * ancho + x) * 3;
                    bSum += arr_temp[index + 0];
                    gSum += arr_temp[index + 1];
                    rSum += arr_temp[index + 2];
                    count++;
                }
            }

            int index = (y * ancho + x) * 3;
            arr_out[index + 0] = (unsigned char)((count > 0) ? (bSum / count) : 0);
            arr_out[index + 1] = (unsigned char)((count > 0) ? (gSum / count) : 0);
            arr_out[index + 2] = (unsigned char)((count > 0) ? (rSum / count) : 0);
        }
    }

    for (int i = 0; i < alto; i++) {
        fwrite(arr_out + (i * ancho * 3), sizeof(unsigned char), ancho * 3, outputImage);
        for (int p = 0; p < padding; p++) {
            fputc(0x00, outputImage);
        }
    }
    *escritas = tam_bytes;

    free(arr_in);
    free(arr_temp);
    free(arr_out);

    fclose(image);
    fclose(outputImage);
}
