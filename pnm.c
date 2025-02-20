/**
 * pnm.c
 * 
 * Ce fichier contient les définitions de types et 
 * les fonctions de manipulation d'images PNM.
 * 
 * @author: Nom Prenom Matricule
 * @date: 
 * @projet: INFO0030 Projet 1
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "pnm.h"


/**
 * Définition du type opaque PNM
 *
 */
struct PNM_t {
   unsigned int height;
   unsigned int width;
   int *pixel_value;

};

typedef enum fileType{
   PBM,
   PGM,
   PPM,
}fileType;

void freePNM(PNM **image) {
    free((*image)->pixel_value);
    free(*image);
    *image = NULL;
}




int skip_commentary_and_stoke_data(FILE *file, PNM *image) {
   int commentairy=0;
   char c;
   int cpt = 0;
   image->width = 0;
   image->height = 0;


   while ((c = fgetc(file)) != EOF) {
      if (c == '#' || commentairy) {
         if (c != '\n') {
            commentairy = 1;
         } else {
            commentairy = 0;
         }
      } 
      else {
            ++cpt;
            fscanf(file,"%d" ,&image->pixel_value[cpt]);
            printf("%c", image->pixel_value[cpt]);
         }
      }
   }

   
   




int load_pnm(PNM **image, char* filename) {
   unsigned height = 0;
   unsigned width = 0;
   char first_line_read[50];


   FILE *file = fopen(filename, "r");
   if (file == NULL) return -2;

   *image = (PNM *)malloc(sizeof(PNM));
   if(*image == NULL){ 
      return -1;
   }
   
   
      char magic_c;
      int magic_n;
      if (fscanf(file, "%c%d", &magic_c, &magic_n) != 2){
         return -2;
      }
      if(magic_c != 'P')
         return -2;

      if (width == 0 && height == 0) {
         fscanf(file, "%d %d", &(width), &(height));
         printf("size %u %u\n", height, width);}
   (*image)->pixel_value = (int*)malloc((height*width*4) * sizeof(int)); 
if ((*image)->pixel_value == NULL) {
   free(*image);
   printf("memory allocation error for pixel_value");
   skip_commentary_and_stoke_data(file, *image );}

   

   skip_commentary_and_stoke_data(file, *image );




   fileType format;
   switch (magic_n)
   {
   case 2:
      format = PGM;
      break;

   case 3:
      format = PPM;
      break;
   case 1:
      format = PBM;
      break;

   default:
      return -3;
   }


   




   /*fget(first_line_read,width,*filename)
   printf('first_line_read = %c', first_line_read)
   */







   return 0;


}

int write_pnm(PNM *image, char* filename){
   return 0;
}




/*int load_pnm(PNM **image, char* filename) {
   FILE *file = fopen(filename, "r");
   if (file == NULL) return -2; // Check if file can be opened

   char extension[4];
   sscanf(filename + strlen(filename) - 3, "%s", extension);
   if (strcmp(extension, "pbm") != 0 && strcmp(extension, "pgm") != 0 && strcmp(extension, "ppm") != 0) {
       fclose(file);
       return -2; // Invalid file extension
   }

   *image = (PNM *)malloc(sizeof(PNM));
   if (*image == NULL) {
       fclose(file);
       return -1; // Memory allocation failure
   }

   if (fscanf(file, "%d %d", &(*image)->width, &(*image)->height) != 2) {
       free(*image);
       fclose(file);
       return -3; // Malformed file content
   }

   (*image)->pixelValue = (unsigned char *)malloc((*image)->width * (*image)->height * sizeof(unsigned char));
   if ((*image)->pixelValue == NULL) {
       free(*image);
       fclose(file);
       return -1; // Memory allocation failure
   }

   for (unsigned int i = 0; i < (*image)->width * (*image)->height; i++) {
       if (fscanf(file, "%hhu", &(*image)->pixelValue[i]) != 1) {
           free((*image)->pixelValue);
           free(*image);
           fclose(file);
           return -3; // Malformed file content
       }
   }

   fclose(file);
   return 0; // Successfully loaded the image
}*/