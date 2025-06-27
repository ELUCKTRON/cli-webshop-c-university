#include "webshop.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int findPrice(char *name, Store *s) {
  for (int i = 0; i < s->size; i++) {
    if (strcmp(name, s->products[i]->name) == 0) {
      return s->products[i]->price;
    }
  }

  return -1;
}

int subtractFromStore(Product *p, Store *s) {
  for (int i = 0; i < s->size; i++) {
    if (strcmp(p->name, s->products[i]->name) == 0) {

      if (s->products[i]->quantity >= p->quantity) {
        s->products[i]->quantity = s->products[i]->quantity - p->quantity;
        return 0;
      } else {
        int missing = (p->quantity) - (s->products[i]->quantity);
        s->products[i]->quantity = 0;
        printf("    << %d %s are missing >>    \n", missing, p->name);
        return missing;
      }
    }
  }
  return -1;
}

int insertToStore(Product *p, Store *s) {

  for (int i = 0; i < s->size; i++) {

    if (strcmp(p->name, s->products[i]->name) == 0) {
      s->products[i]->quantity = s->products[i]->quantity + p->quantity;
      return 1;
    }
  }

  if (s->size == s->maxsize) {
    s->maxsize = 2 * s->size;
    s->products = realloc(s->products, s->maxsize * sizeof(Product));
  }
  s->products[s->size] = p;
  s->size = s->size + 1;

  return 0;
}

void cleanupStore(Store *s) {
  for (int i = 0; i < s->size; i++) {
    free(s->products[i]->name);
    free(s->products[i]);
  }
  free(s->products);
  free(s);
}

int insertToCart(Product *p, Cart *c) {
  for (int i = 0; i < c->size; i++) {
    if (strcmp(p->name, c->products[i]->name) == 0) {
      c->products[i]->quantity = c->products[i]->quantity + p->quantity;
      return 1;
    }
  }

  if (c->size == c->maxsize) {
    c->maxsize = 2 * c->size;
    c->products = realloc(c->products, c->maxsize * sizeof(Product));
  }

  c->products[c->size] = p;
  c->size = c->size + 1;

  return 0;
}

void cleanupCart(Cart *c) {
  for (int i = 0; i < c->size; i++) {
    free(c->products[i]->name);
    free(c->products[i]);
  }
  free(c->products);
  free(c);
}

void StoreReader(Store *store) {
  for (int i = 0; i < store->size; i++) {
    printf("Item Name : %s , Item Price : %d , Item Quantity : %d  \n",
           store->products[i]->name, store->products[i]->price,
           store->products[i]->quantity);
  }
}

void CartReader(Cart *Cart) {
  for (int i = 0; i < Cart->size; i++) {
    printf("Item Name : %s , Item Quantity : %d  \n", Cart->products[i]->name,
           Cart->products[i]->quantity);
  }
}