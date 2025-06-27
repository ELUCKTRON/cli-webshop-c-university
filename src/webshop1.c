#include "webshop.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  Store *store = malloc(sizeof(Store));
  store->size = 0;
  store->maxsize = 100;
  store->products = malloc(sizeof(Product) * 100);

  Cart *cart = malloc(sizeof(Cart));
  cart->size = 0;
  cart->maxsize = 100;
  cart->products = malloc(sizeof(Product) * 100);

  int command;
  char C = 't';
  while (C == 't') {
    printf("\n");
    printf("Welcome to the store! \n");
    printf(" Items Availble in store are : \n");
    StoreReader(store);
    printf("\n");
    printf(" Items in the Cart are  : \n");
    CartReader(cart);
    printf("\n");

    printf("Enter command : \n");
    printf("1.Load webshop store from a file\n2.Write the content of the store "
           "to a file\n3.Insert an item to cart\n4.Get the price of "
           "cart\n5.Buy the products\n6.Exit the program\n");

    if (scanf("%d", &command) != 1) {
      printf("Invalid input. Please enter a number.\n");
      while (getchar() != '\n')
        ;
      continue;
    }

    switch (command) {
    case 1:

      if (store->size > 0) {
        cleanupStore(store);

        store = malloc(sizeof(Store));
        store->size = 0;
        store->maxsize = 100;
        store->products = malloc(sizeof(Product) * 100);
      }

      printf("Type the Webshop file name : ");
      char fileName[100];
      scanf("%s", fileName);

      FILE *myfile = fopen(fileName, "r");
      if (myfile == NULL) {
        printf("File not found\n");
        break;
      }

      int lineCounter = 1;
      char buffer[100] = {0};

      while (fgets(buffer, sizeof buffer, myfile) != NULL) {
        char str[20];
        int num1, num2;

        int result = sscanf(buffer, "%s %d %d", str, &num1, &num2);

        if (result == 3) {

          Product *p = malloc(sizeof(Product));
          p->name = malloc(strlen(str) + 1);
          strcpy(p->name, str);
          p->price = num1;
          p->quantity = num2;

          int x = insertToStore(p, store);

          if (x == 1) {
            free(p->name);
            free(p);
          }
        } else {
          printf("Error: Invalid input format at line %d\n", lineCounter);
        }

        lineCounter++;
        memset(buffer, 0, 100);
      }

      printf("    << Store Loaded >>    \n ");
      fclose(myfile);
      break;
    case 2:
      if (store->size == 0) {
        printf("    << there is no item in the store , Load webshop first >>   "
               " \n");
        break;
      }

      printf("Please Give me a File name to Create : ");
      char fileName2[100];
      scanf("%s", fileName2);
      FILE *myfile2 = fopen(fileName2, "w");
      if (myfile2 == NULL) {
        printf("Error creating file!\n");
        return 1;
      }

      for (int i = 0; i < store->size; i++) {
        if (i == store->size - 1) {
          fprintf(myfile2, "%s %d %d", store->products[i]->name,
                  store->products[i]->price, store->products[i]->quantity);
        } else {
          fprintf(myfile2, "%s %d %d\n", store->products[i]->name,
                  store->products[i]->price, store->products[i]->quantity);
        }
      }

      printf("   << Store Printed to the file %s >>   \n", fileName2);
      fclose(myfile2);
      break;
    case 3:
      printf("Name and quanity of the item you want to add to cart with one "
             "space : \n");
      char name[100];
      int quantity;
      scanf("%s %d", name, &quantity);

      int price = findPrice(name, store);
      if (price >= 0) {
        Product *p = malloc(sizeof(Product));
        p->name = malloc(strlen(name) + 1);
        strcpy(p->name, name);
        p->price = price;
        p->quantity = quantity;

        int x = insertToCart(p, cart);
        if (x == 1) {
          free(p->name);
          free(p);
        }

        printf("   << item added to the cart >>   \n");
        break;
      } else {
        printf("   << Item not found in the store >>   \n");
        break;
      }
      break;
    case 4:
      if (cart->size == 0) {
        printf("   << there is no item in the cart , Add items first >>   \n");
        break;
      }

      int cartPrice = 0;
      for (int i = 0; i < cart->size; i++) {
        cartPrice += cart->products[i]->price * cart->products[i]->quantity;
      }

      printf("   << the price of your cart is %d :  >>   \n", cartPrice);
      break;
    case 5:
      if (cart->size == 0) {
        printf("   << there is no item in the cart , Add items first >>   \n");
        break;
      }

      int AvailblePrice = 0;
      for (int i = 0; i < cart->size; i++) {
        int p = subtractFromStore(cart->products[i], store);
        if (p == -1) {
          printf("    << this item is added from different store >>   ");
        } else if (p == 0) {
          AvailblePrice +=
              cart->products[i]->price * cart->products[i]->quantity;
        } else {
          AvailblePrice +=
              ((cart->products[i]->price) * (cart->products[i]->quantity - p));
        }
      }
      printf(
          "   << Thank you for buying from us your total availble : %d >>   \n",
          AvailblePrice);
      cleanupCart(cart);

      cart = malloc(sizeof(Cart));
      cart->size = 0;
      cart->maxsize = 100;
      cart->products = malloc(sizeof(Product) * 100);

      break;
    case 6:
      cleanupStore(store);
      cleanupCart(cart);

      printf("   << GoodBye >>   \n");
      C = 'f';
      break;
    default:
      printf("   << Choose between 1-6 for your program >>   \n");
      break;
    }
  }
}