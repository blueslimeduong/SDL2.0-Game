#include <iostream>
#include "commonfunc.h"

bool checkCollision(const SDL_Rect &a,const SDL_Rect &b )
{
    // The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;  //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;

}
//bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2)
//{
//  int left_a = object1.x;
//  int right_a = object1.x + object1.w;
//  int top_a = object1.y;
//  int bottom_a = object1.y + object1.h;
//
//  int left_b = object2.x;
//  int right_b = object2.x + object2.w;
//  int top_b = object2.y;
//  int bottom_b = object2.y + object2.h;
//
//  // Case 1: size object 1 < size object 2
//  if (left_a > left_b && left_a < right_b)
//  {
//    if (top_a > top_b && top_a < bottom_b)
//    {
//      return true;
//    }
//  }
//
//  if (left_a > left_b && left_a < right_b)
//  {
//    if (bottom_a > top_b && bottom_a < bottom_b)
//    {
//      return true;
//    }
//  }
//
//  if (right_a > left_b && right_a < right_b)
//  {
//    if (top_a > top_b && top_a < bottom_b)
//    {
//      return true;
//    }
//  }
//
//  if (right_a > left_b && right_a < right_b)
//  {
//    if (bottom_a > top_b && bottom_a < bottom_b)
//    {
//      return true;
//    }
//  }
//
//  // Case 2: size object 1 < size object 2
//  if (left_b > left_a && left_b < right_a)
//  {
//    if (top_b > top_a && top_b < bottom_a)
//    {
//      return true;
//    }
//  }
//
//  if (left_b > left_a && left_b < right_a)
//  {
//    if (bottom_b > top_a && bottom_b < bottom_a)
//    {
//      return true;
//    }
//  }
//
//  if (right_b > left_a && right_b < right_a)
//  {
//    if (top_b > top_a && top_b < bottom_a)
//    {
//      return true;
//    }
//  }
//
//  if (right_b > left_a && right_b < right_a)
//  {
//    if (bottom_b > top_a && bottom_b < bottom_a)
//    {
//      return true;
//    }
//  }
//
//   // Case 3: size object 1 = size object 2
//  if (top_a == top_b && right_a == right_b && bottom_a == bottom_b)
//  {
//    return true;
//  }
//
//  return false;
//}
