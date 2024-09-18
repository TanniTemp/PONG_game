#include <iostream>
#include <raylib.h>

using namespace std;
int player_score =0;
int cpu_score =0;
bool isSinglePlayer = true; 
class Ball{
    public:
    float x,y;
    int speed_x, speed_y;
    int radius;

    void Draw(){
        DrawCircle(x, y,radius,WHITE);
    }
   
   void Update(){
    x+=speed_x;
    y+=speed_y;
    if(y+radius>=GetScreenHeight()|| y-radius<=0){
        speed_y*=-1;
    }
    if(x+radius>=GetScreenWidth()){
        cpu_score++;
        ResetBall();
    } if(x-radius<=0){
        player_score++;
        ResetBall();
    }
   }
   void ResetBall(){
    x=GetScreenWidth()/2;
    y = GetScreenHeight()/2;
  int  speed_choices[2] ={-1,1};
  speed_x *= speed_choices[GetRandomValue(0,1)];
  speed_y *= speed_choices[GetRandomValue(0,1)];
   }
};  

class Paddle{
    protected:
    void LimitMovement(){
         if(y<=0){
            y=0;
        }
        if(y+height>=GetScreenHeight()){
            y= GetScreenHeight()-height;
        }
    }
    public:
    float x,y;
    float width,height;
    int speed;
    void Draw(){
    DrawRectangle(x,y, width, height,WHITE );
    }
    void Update(){
        if(IsKeyDown(KEY_UP)){
            y=y-speed;
        }
        if(IsKeyDown(KEY_DOWN)){
            y=y+speed;
        }
       LimitMovement();
    }   
};

class CpuPaddle: public Paddle{
        public: 
        void Update(int ball_y){
                if(y+height/2>ball_y){
                    y=y-speed;
                }
                if(y+height/2<=ball_y){
                    y=y+speed; 
                }
                LimitMovement();
        }
};
class Player2: public Paddle{
        public: 
        void Update(){
                 if(IsKeyDown(KEY_W)){
            y=y-speed;
        }
        if(IsKeyDown(KEY_S)){
            y=y+speed;
        }
       LimitMovement();
        }
};
Ball ball;
Paddle player;
CpuPaddle cpu;
Player2 player2;

enum GameState {
 MENU,
 GAME
};
int main () {
    GameState gameState = MENU;
   cout<<"starting the game"<<endl;
    const int screen_width= 1280;
    const int screen_height= 800;
    ball.radius = 20;
    ball.x= screen_width/2;
    ball.y= screen_height/2;
    ball.speed_x=7;
    ball.speed_y=7;
    player.width=25;
    player.height=120;
    player.x = screen_width-player.width-10;
    player.y= screen_height/2-player.height/2;
    player.speed=6;

    cpu.height=120;
    cpu.width=25;
    cpu.x=10;
    cpu.y=screen_height/2-cpu.height/2;
    cpu.speed=6;
    

    player2.height=120;
    player2.width=25;
    player2.x=10;
    player2.y=screen_height/2-cpu.height/2;
    player2.speed=6;
   InitWindow(screen_width, screen_height, "My Pong Game!");

    SetTargetFPS(60);
    while(WindowShouldClose()==false){
        //update
        BeginDrawing();
        ClearBackground(BLACK);

        switch (gameState)
        {
        case MENU:
            DrawText("PONG",screen_width / 2 - MeasureText("PONG GAME", 40) / 2, screen_height / 4, 40, WHITE);
            DrawText("Press 1 for Single Player", screen_width / 2 - MeasureText("Press 1 for Single Player", 20) / 2, screen_height / 2, 20, WHITE);
            DrawText("Press 2 for Multiplayer", screen_width / 2 - MeasureText("Press 2 for Multiplayer", 20) / 2, screen_height / 2 + 30, 20, WHITE);
              if (IsKeyPressed(KEY_ONE)) {
                isSinglePlayer = true;  // Set to single player mode
                gameState = GAME;  // Move to the GAME state
            }
            if (IsKeyPressed(KEY_TWO)) {
                isSinglePlayer = false;  // Set to multiplayer mode
                gameState = GAME;  // Move to the GAME state
            }
            break;
        
        


        case GAME:
          ball.Update();
          player.Update();
        if(isSinglePlayer){
            cpu.Update(ball.y);
        }  
        else{
            player2.Update();
        }
            //checking collision
            if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{player.x,player.y, player.width, player.height}))
            {
                ball.speed_x*=-1;
            }
          if(isSinglePlayer){
              if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{cpu.x,cpu.y, cpu.width, cpu.height}))
            {
                ball.speed_x*=-1;
            }
          }
          else{
              if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{player2.x,player2.y, player2.width, player2.height}))
            {
                ball.speed_x*=-1;
            }
          }

               //Draw 
            

            DrawLine(screen_width/2,0,screen_width/2,screen_height,WHITE);
            ball.Draw();
          if (isSinglePlayer) {
                cpu.Draw();  
            } else {
                player2.Draw(); 
            }
           DrawText(TextFormat("%i",cpu_score),screen_width/4-20,20, 80 ,WHITE);
           DrawText(TextFormat("%i",player_score),3*screen_width/4-20,20, 80 ,WHITE);
           
            player.Draw();
        }
        EndDrawing();
    }

   CloseWindow();
    return 0;
}