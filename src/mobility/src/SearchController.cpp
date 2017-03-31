#include "SearchController.h"

SearchController::SearchController() {
  //rng = new random_numbers::RandomNumberGenerator();
}

/**
 * This code implements a basic random walk search.
 */
geometry_msgs::Pose2D SearchController::search(geometry_msgs::Pose2D currentLocation, double thetas[], int roverNumb, int *stepMove) {
  geometry_msgs::Pose2D goalLocation;

  int init = *stepMove;
  double dis[2];
  dis[1]=1;
  if(init==0) {
    //select new heading from Gaussian distribution around current heading
    goalLocation.theta = currentLocation.theta;

    //select new position 50 cm from current location
    goalLocation.x = currentLocation.x + (0.4 * cos(goalLocation.theta));
    goalLocation.y = currentLocation.y + (0.4 * sin(goalLocation.theta));

    *stepMove = 1;
    return goalLocation;
  }

  if(roverNumb == 1){
    if(init==1){

      goalLocation.theta = 0;
      goalLocation.x = currentLocation.x + ((dis[1]*init) * cos(goalLocation.theta));
      goalLocation.y = currentLocation.y + ((dis[1]*init) * sin(goalLocation.theta));

      *stepMove = *stepMove +1;
    }
    else if (init%4==2) {
      goalLocation.theta = thetas[1];

      goalLocation.x = currentLocation.x + (0.4 * cos(goalLocation.theta));
      goalLocation.y = currentLocation.y + (0.4 * sin(goalLocation.theta));

      *stepMove = *stepMove +1;
    }
    else if(init%4==3){

      goalLocation.theta ==M_PI;

      goalLocation.x = currentLocation.x + ((dis[1]*init) * cos(goalLocation.theta));
      goalLocation.y = currentLocation.y + ((dis[1]*init) * sin(goalLocation.theta));
      init = 4;
      *stepMove = init;
    }
    else if (init == 4){
      *stepMove = 1;
      goalLocation.theta = thetas[0];

      goalLocation.x = currentLocation.x + (0.4 * cos(goalLocation.theta));
      goalLocation.y = currentLocation.y + (0.4 * sin(goalLocation.theta));
    }

  }
  else if(roverNumb==2){
    if(init%4==1){

      *stepMove = *stepMove +1;
      goalLocation.theta = 4*M_PI/6;
      goalLocation.x = currentLocation.x + ((dis[1]*init) * cos(goalLocation.theta));
      goalLocation.y = currentLocation.y + ((dis[1]*init) * sin(goalLocation.theta));
    }
    else if (init%4==2) {

      *stepMove = *stepMove +1;
      goalLocation.theta = thetas[1];

      goalLocation.x = currentLocation.x + (0.4 * cos(goalLocation.theta));
      goalLocation.y = currentLocation.y + (0.4 * sin(goalLocation.theta));
    }
    else if(init%4==3){

      goalLocation.theta ==-2*M_PI/6;

      goalLocation.x = currentLocation.x + ((dis[1]*init) * cos(goalLocation.theta));
      goalLocation.y = currentLocation.y + ((dis[1]*init) * sin(goalLocation.theta));
      init = 4;
      *stepMove= init;
    }
    else if (init == 4){

      *stepMove = 1;
      goalLocation.theta = thetas[0];

      goalLocation.x = currentLocation.x + (0.4 * cos(goalLocation.theta));
      goalLocation.y = currentLocation.y + (0.4 * sin(goalLocation.theta));
    }

  }
  else if (roverNumb == 3){
    if(init%4==1){

      *stepMove = *stepMove +1;
      goalLocation.theta = -4*M_PI/6;
      goalLocation.x = currentLocation.x + ((dis[1]*init) * cos(goalLocation.theta));
      goalLocation.y = currentLocation.y + ((dis[1]*init) * sin(goalLocation.theta));
    }
    else if (init%4==2) {

      *stepMove = *stepMove +1;
      goalLocation.theta = thetas[1];

      goalLocation.x = currentLocation.x + (0.4 * cos(goalLocation.theta));
      goalLocation.y = currentLocation.y + (0.4 * sin(goalLocation.theta));
    }
    else if(init ==3){

      goalLocation.theta ==2*M_PI/6;;

      goalLocation.x = currentLocation.x + ((dis[1]*init) * cos(goalLocation.theta));
      goalLocation.y = currentLocation.y + ((dis[1]*init) * sin(goalLocation.theta));
      init = 4;
      *stepMove = init;
    }
    else if(init ==4){

      *stepMove = 1;
      goalLocation.theta = thetas[0];

      goalLocation.x = currentLocation.x + (0.4 * cos(goalLocation.theta));
      goalLocation.y = currentLocation.y + (0.4 * sin(goalLocation.theta));
    }

  }

  return goalLocation;

  /*geometry_msgs::Pose2D goalLocation;

  //select new heading from Gaussian distribution around current heading
  goalLocation.theta = rng->gaussian(currentLocation.theta, 0.25);

  //select new position 50 cm from current location
  goalLocation.x = currentLocation.x + (0.5 * cos(goalLocation.theta));
  goalLocation.y = currentLocation.y + (0.5 * sin(goalLocation.theta));

  return goalLocation;*/
}

/**
 * Continues search pattern after interruption. For example, avoiding the
 * center or collisions.
 */
geometry_msgs::Pose2D SearchController::continueInterruptedSearch(geometry_msgs::Pose2D currentLocation, geometry_msgs::Pose2D oldGoalLocation) {
  geometry_msgs::Pose2D newGoalLocation;


  //remainingGoalDist avoids magic numbers by calculating the dist
  double remainingGoalDist = hypot(oldGoalLocation.x - currentLocation.x, oldGoalLocation.y - currentLocation.y);

  //this of course assumes random walk continuation. Change for diffrent search methods.
  newGoalLocation.theta = oldGoalLocation.theta;
  newGoalLocation.x = currentLocation.x + (0.50 /** cos(oldGoalLocation.theta)*/); //(remainingGoalDist * cos(oldGoalLocation.theta));
  newGoalLocation.y = currentLocation.y + (0.50 /** sin(oldGoalLocation.theta)*/); //(remainingGoalDist * sin(oldGoalLocation.theta));

  return newGoalLocation;

  /*//remainingGoalDist avoids magic numbers by calculating the dist
  double remainingGoalDist = hypot(oldGoalLocation.x - currentLocation.x, oldGoalLocation.y - currentLocation.y);

  //this of course assumes random walk continuation. Change for diffrent search methods.
  newGoalLocation.theta = oldGoalLocation.theta;
  newGoalLocation.x = currentLocation.x + (0.50 * cos(oldGoalLocation.theta)); //(remainingGoalDist * cos(oldGoalLocation.theta));
  newGoalLocation.y = currentLocation.y + (0.50 * sin(oldGoalLocation.theta)); //(remainingGoalDist * sin(oldGoalLocation.theta));

  return newGoalLocation;*/
}
