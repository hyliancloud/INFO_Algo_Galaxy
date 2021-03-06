/**
 * \file twi_bodies.c
 * \brief Will create two bodies and make them rotate around each other.
 * \author Marti Emilie & Soustre Ludovic
 * \version 0.1
 * \date April 16th 2019
 *
 * Test programm given by M.Thapper to begin the project.
 * Two bodies are created and rotate around each other.
 *
 */

#include <stdio.h>
#include <math.h>
#include <MLV/MLV_all.h>

#include "../headers/galaxy_manager.h"
#include "../headers/galaxy.h"
#include "../headers/graphic.h"
#include "../headers/physics.h"

void update_all_bodies(Galaxy* galaxy)
{
    double t = 0.0;

    int i, j;

    display_window();
    
    while(1)
    {
        for(i = 0; i < galaxy->numberOfBodies; i++)
        {
            galaxy->bodies[i]->fx = 0.0f;
            galaxy->bodies[i]->fy = 0.0f;

            for(j = 0; j < galaxy->numberOfBodies; j++)
                if(i != j)
                    update_force(galaxy->bodies[i], galaxy->bodies[j]);

            update_position(galaxy->bodies[i]);
        }

        MLV_draw_filled_rectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, MLV_COLOR_BLACK);
        draw_bodies(galaxy);
        
        MLV_update_window();

        t += dt;
        MLV_wait_milliseconds(10);
    }
}

void update_force(Body* B1, Body* B2)
{
    double dx, dy, dist;

    dx = B2->px-B1->px;
    dy = B2->py-B1->py;
    
    dist = sqrt(dx*dx+dy*dy);

    B1->fx += (G*B1->mass*B2->mass/(dist*dist+(C*C)))*(dx/dist); 
    B1->fy += (G*B1->mass*B2->mass/(dist*dist+(C*C)))*(dy/dist); 
}

void update_velocity(Body* body)
{
    body->vx += dt*body->fx/body->mass;
    body->vy += dt*body->fy/body->mass;
}

void update_position(Body* body)
{
    update_velocity(body);

    body->px += dt*body->vx;
    body->py += dt*body->vy;
}