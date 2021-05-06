#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include "unity.h"
#include "function.h"

/*
void test_order_create() {
  struct Customer c;
  c.name = "Farha";
  struct Order *o = order_create(&c);
  TEST_ASSERT_NOT_NULL_MESSAGE(o,"order_create returned a null pointer");
  TEST_ASSERT_EQUAL_PTR_MESSAGE(&c,o->customer,"order create returned an order with the wrong customer");
  TEST_ASSERT_NULL_MESSAGE(o->dishes,"order_create returned an order with a Non-NULL array");
  TEST_ASSERT_EQUAL_INT(0,o->order_length);



}

void test_order_add_dishes()
{
  struct Dish d;
  d.name ="pasta";
  
}
*/
void test_createWindow(){
	SDL_Window *window = createWindow("window");
	TEST_ASSERT_NOT_NULL (window);
}

void test_createRenderer(){
	SDL_Window *window = createWindow("window");
	SDL_Renderer *renderer = createRenderer(window);
	TEST_ASSERT_NOT_NULL (renderer);
}

void test_count(){
	int test[3][3] = {
		{0,0,0},
		{0,1,1},
		{1,1,0}
	};
	GRID_HEIGHT=3;
	GRID_WIDTH=3;
	TEST_ASSERT_EQUAL_INT (3, count(test, 1, 1));
	TEST_ASSERT_EQUAL_INT (1, count(test, 0, 0));
	TEST_ASSERT_EQUAL_INT (3, count(test, 0, 1));
}

void test_update(){
	GRID_HEIGHT=3;
	GRID_WIDTH=3;
	int test[3][3] = {
		{0,0,0},
		{0,1,1},
		{1,1,0}
	};
	update(test);
	TEST_ASSERT_EQUAL_INT (1, buffer1[1][2]);
	TEST_ASSERT_EQUAL_INT (0, buffer1[0][0]);
	TEST_ASSERT_EQUAL_INT (1, buffer1[1][1]);
}


void test_save_file(){
	int a = 0;
	GRID_HEIGHT=1;
	GRID_WIDTH=1;
	int v, h; 
    for(v = 0; v < GRID_HEIGHT; v++){
        for(h = 0; h < GRID_WIDTH; h++){
            buffer1[v][h]=0;
        }
    }
	save_file();
	FILE* fp;
	fp = fopen("file.txt", "r");
    if ((fp = fopen("file.txt", "r")) == NULL) a=1;
    fclose(fp);
    TEST_ASSERT_EQUAL_INT (0, a);
}

void test_load_file(){
	int a = 0;
	char check;
	int counth = 0;
    int countw = 0;
	GRID_HEIGHT=3;
	GRID_WIDTH=3;
	int v, h; 
    for(v = 0; v < GRID_HEIGHT; v++){
        for(h = 0; h < GRID_WIDTH; h++){
            buffer1[v][h]=0;
        }
    }
	save_file();
	FILE* fp;
	if(fp){
        while((check=fgetc(fp)) != EOF){
            if(check=='\n') counth++;
            else if(check==' ');
            else countw++;
        }
        GRID_WIDTH=countw/counth;
        GRID_HEIGHT=counth;
        fclose(fp);
    }
    TEST_ASSERT_EQUAL_INT (3, GRID_HEIGHT);
    TEST_ASSERT_EQUAL_INT (3, GRID_WIDTH);
}


void setUp(){

}
void tearDown(){

}

int main(int argc,char *argv[]) {
  UNITY_BEGIN();
	RUN_TEST(test_createWindow);
	RUN_TEST(test_createRenderer);
	RUN_TEST(test_count);
	RUN_TEST(test_update);
	RUN_TEST(test_save_file);
	RUN_TEST(test_load_file);

  return UNITY_END();
}
