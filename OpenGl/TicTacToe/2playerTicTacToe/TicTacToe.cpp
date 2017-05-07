#include "stdafx.h" 
#include <stdlib.h> 
#include <glut.h> 
#include <iostream> 
#include <math.h> 
#include <time.h> 
#include <string.h> 
  int board[3][3]; // board for gameplay  
int turn;// current move 
int result; // Result of the game  
bool over;   // Is the game Over? 
  /*윈도우 좌표=(300,350)이지만 계산하기 쉽게 y좌표 구할 때는 50을 빼서 계산 
  board[0][0]=(0~100, 0~100)  board[0][1]=(101~200, 0~100)   board[0][2]=(201~300, 0~100) 
  board[1][0]=(0~100, 101~200)  board[1][1]=(101~200, 101~200)   board[1][2]=(201~300, 101~200) 
  board[2][0]=(0~100, 201~300)    board[2][1]=(101~200, 201~300)     board[2][2]=(201~300, 201~300)  
  player1차례면 X로 표시 player2차례면 O로 표시 */
 /*   Sets the board for Tic Tac Toe  */  
void Intialize() //세팅함수 
{   turn=1; //player1부터 시작  
 for(int i=0;i<3;i++) 
 {  
	 for(int j=0;j<3;j++) 
		 board[i][j]=0; //9개 판 모두 0으로 세팅(아직 아무도 플레이 안한 상태) 
 } 
} 
/*   Called when any key from keyboard is pressed  */
void OnKeyPress(unsigned char key,int x,int y) //게임 종료 후 재시작 여부 묻고 재시작하는 함수 
{   
	switch(key)   
	{    
		case 'y': //게임 종료 후 재시작 할 때   
			if(over==true)    
			{    
				over=false;    
				Intialize(); //다시 초기화시킨 후 재시작   
			}  
			break;
   case 'n': //재시작 안하면   
			if(over==true)    
			{     exit(0); //종료  
			}   
			break;   
		default:    
			exit(0);   
	} 
}    /*   Called when Mouse is clicked   */ 
void OnMouseClick(int button,int state,int x,int y) // x,y는 현재 화면 좌표  
{   if(over==false && button==GLUT_LEFT_BUTTON && state==GLUT_DOWN) //게임이 종료 되기전까지 반복해서 진행. 왼쪽 마우스 클릭으로 게임 진행 
{
	if(turn==1) //player1 차례일 때   
	{   
		if(board[(y-50)/100][x/100]==0) //윈도우 크기가 (300,350)이니까 y값에서 50을 뺀 후 100으로 나눠야 세 영역으로 나눠짐 x는 원래부터 300이니까 바로 100으로 나누면 ok  
	{   
		board[(y-50)/100][x/100]=1; //선택된 영역이 아무도 선택하지 않았던(0을 가지는 값)영역이라면 1로 바꾸기(player1차례니까 1로 바꾸는 것) 
			turn=2; //player2차례 
		}  
	}  
	else if(turn==2)  
	{   
		if(board[(y-50)/100][x/100]==0)    
		{     board[(y-50)/100][x/100]=2; //선택된 영역이 아무도 선택하지 않았던(0을 가지는 값)영역이라면 2로 바꾸기(player2차례니까 2로 바꾸는 것)   
		 turn=1;//player1차례로 돌려주기  
		}   
	}  
} 
}  
 /*   Utility function to draw string    */  
void DrawString(void *font,const char s[],float x,float y) // 누구차례인지 string함수 
{   unsigned int i; 
 glRasterPos2f(x,y); 
 for(i=0;i<strlen(s);i++)  
 {   
	 glutBitmapCharacter(font,s[i]);  
 } 
}  
 /*   Function to draw up the horizontal and vertical lines  */  
void DrawLines() //9개의 영역으로 나눌 선분 만드는 함수 
{   glBegin(GL_LINES); //정점 두개로 선분 만들기 
 glColor3f(0,0,0);   
 glVertex2f(100,50);  
 glVertex2f(100,340);  
 glVertex2f(200,340);  
 glVertex2f(200,50);  
 glVertex2f(0,150); 
 glVertex2f(300,150);  
 glVertex2f(0,250);  
 glVertex2f(300,250);   
 glEnd();   
} 
/*  Utility function to draw the circle */ 
void DrawCircle(float cx, float cy, float r, int num_segments)  //원 만드는 함수 num_segments란??????????????????????????????? 원만드는거 다시 공부???????????????????????????????????
{    
	glBegin(GL_LINE_LOOP);    
	for (int i = 0; i < num_segments; i++)       
	{         
		float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);//get the current angle  현재의 angle 얻기       
		float x = r * cosf(theta);//calculate the x component  얻은 angle토대로 x좌표 구하기        
		float y = r * sinf(theta);//calculate the y component  얻은 angle토대로 y좌표 구하기        
		glVertex2f(x + cx, y + cy);//output vertex    
	}     glEnd(); } 
/*  Function to draw the cross and circle of Tic Tac Toe */ 
void DrawXO() //X와 O그리는 함수
{  
	for(int i=0;i<3;i++) 
	{   
		for(int j=0;j<3;j++)   
		{    
			if(board[i][j]==1) //player1이 영역 선택할 때 x로 나타내는 것 
			{     
				glBegin(GL_LINES);     
				glVertex2f(50 +( j * 100) - 25, 100 + (i * 100) - 25);//*************원래 괄호 안 쳐져 있었음 우선순위에 따라 *부터 계산되는건 맞지만 헷갈리니까 괄호침=> 좋은 코드   
				glVertex2f(50 + (j * 100) + 25, 100 + (i * 100) + 25); //만약 [0][0]이면 (25,75) (75,125)    (25,125) (75,75)의 선분 그려짐   
				glVertex2f(50 + (j * 100) - 25, 100 + (i * 100) + 25);    
				glVertex2f(50 + (j * 100) + 25, 100 + (i * 100) - 25);    
				glEnd();    }   
			else if(board[i][j]==2) //player2가 영역 선택할 때 o로 나타내는 것  
			{       
				DrawCircle(50 + j*100 , 100 + i*100 , 25 , 15);    }   }  } } 
/*  Function to check if there is any winner  */
bool CheckWinner() //승자가 있는지 check하는 함수
{  int i, j;  // horizontal(수평의)check 
 for(i=0;i<3;i++)  {   for(j=1;j<3;j++)   { 
	 if(board[i][0]!=0 && board[i][0]==board[i][j])    {     if(j==2)     {      return true;     }    }    else     break;   }  }  // vertical check 
 for(i=0;i<3;i++)  {   for(j=1;j<3;j++)   {    if(board[0][i]!=0 && board[0][i]==board[j][i])    {     if(j==2)      return true;    }    else     break;   }  }  // Diagonal check  
 if((board[0][0]!=0 && board[0][0]==board[1][1] && board[0][0]==board[2][2])   || (board[2][0]!=0 && board[2][0]==board[1][1] && board[2][0]==board[0][2]))   return true;  return false; } 
/*  function to check if there is draw */ bool CheckIfDraw() {  int i, j;  bool draw;  for(i=0;i<3;i++)  {    for(j=0;j<3;j++)   {     if(board[i][j]==0)     return false;   }  }  return true;  } 
/*  Function to display up everything */ void Display() {  glClear(GL_COLOR_BUFFER_BIT);  glClearColor(1, 1, 1, 1);  glColor3f(0, 0, 0);  if(turn == 1)   DrawString(GLUT_BITMAP_HELVETICA_18, "Player1's turn", 100, 30);   else   DrawString(GLUT_BITMAP_HELVETICA_18, "Player2's turn", 100, 30);  
							 DrawLines();  DrawXO();    if(CheckWinner() == true)  {   if(turn == 1)   {    over = true;    result = 2;   }   else   {    over = true;    result = 1;    }  }  else if(CheckIfDraw() == true)  {   over = true;   result = 0;  }  if(over == true)  {   DrawString(GLUT_BITMAP_HELVETICA_18, "Game Over", 100, 160);   if(result == 0)   
								 DrawString(GLUT_BITMAP_HELVETICA_18, "It's a draw", 110, 185);   if(result == 1)    DrawString(GLUT_BITMAP_HELVETICA_18, "Player1 wins", 95, 185);   if(result == 2)    DrawString(GLUT_BITMAP_HELVETICA_18, "Player2 wins", 95, 185);   DrawString(GLUT_BITMAP_HELVETICA_18, "Do you want to continue (y/n)", 40, 210);  }
							 glutSwapBuffers(); } 
/*  Function to reshape */ void Reshape(int x, int y) {  glViewport(0, 0, x, y);  glMatrixMode(GL_PROJECTION);  glLoadIdentity();  glOrtho(0, x, y, 0, 0, 1);  glMatrixMode(GL_MODELVIEW); } 
/*  Driver Function */ int main(int argc, char **argv) {  printf("hello");  Intialize();  glutInit(&argc,argv);  glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);  glutInitWindowPosition(550,200);  glutInitWindowSize(300,350); //윈도우 사이즈는 x=300, y=350
							glutCreateWindow("Tic Tac Toe"); //윈도우 명 
							glutReshapeFunc(Reshape);  glutDisplayFunc(Display);  glutKeyboardFunc(OnKeyPress);  glutMouseFunc(OnMouseClick);  glutIdleFunc(Display);     glutMainLoop();     return 0; } 
