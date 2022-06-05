#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>; // for exitting the function 
#include <string>
using std::ifstream; 
using namespace std;



double Q[4][4][4], V[4][4], R[4][4]; // Q-Array to update the value iteration algorithm and Value iteration matrix
int Policy[4][4]; 



void initializing_gridworld() // initializing the value array V and the reward R array to the initial values of the system 
{
	int i, j; 

	for (i = 2; i >= 0; i--)
	{
		for (j = 0; j <= 3; j++)
		{
			V[i][j] = 0.0;  // initializing the gridworld with 0s
			R[i][j] = -0.04; // reward for every step we take 
		}
	}

	 R[2][3] = 1.0;
	 V[2][3] = 1.0;
	 R[1][3] = -1.0 ;
	 V[1][3] = -1.0 ;
}


void printPolicy()
{
	int i, j; 
	// prints the policy with arrows signifying the direction 

	for (i = 2 ; i >= 0; i--)
	{
		for (j = 0; j <= 3; j++)
		{
			if (i == 2 && j == 3)
			{
				cout << " o ";
				continue; 
			}

			
			
			
			if (i == 1 && j == 1)
			{
				cout << "  W "; 
				continue; 
			}
			


			switch (Policy[i][j]) 
			{
			case 0: cout << " ^"; 
				break;
			case 1: cout << " v";
				break;
			case 2: cout << " <";
				break;
			case 3: cout << " >"; 
				break;
			}
			cout << "  "; 

		}
		cout << endl; 
	}

}




void printV()
{
	int i, j; 


	for (i = 2; i >= 0; i--)
	{
		for (j = 0; j <= 3; j++)
		{
			cout << setprecision(3) << V[i][j] << "\t";
		}
		cout << endl;

	}
}




void printQ(int i, int j) // returns the values for the choices up, down, left and right 
{


		for (int a = 0; a < 4; a++)
		{
			cout << Q[i][j][a] << " ";
		}
		cout << endl;
}



void valueIteration(double gamma) // computes the values for the value array by doing value iteration 
{
	int l, a, maxQindex, i, j; 
	double maxQ;


	for (l = 0; l < 1000; l++) // number of iterations 
	{
		for (i = 2; i>= 0; i--)
		{
			for (j = 3; j >= 0; j--)
			{
				if (i == 2 && j == 3 || i == 1 && j == 3)
					continue;


				maxQ = -1000000.0;





				for (a = 0; a <= 3; a++)
				{






					// we need to check if the current action is legal or not 
					switch (a)
					{








					case 0:
						// going upwards

						Q[i][j][a] = R[i][j]; // getting the immediate reward


						if (i + 1 <= 2 && i + 1 >= 0 && j != 1)
						{


							Q[i][j][a] += gamma * 0.8 * V[i + 1][j];
						}
						else
						{

							Q[i][j][a] += gamma * 0.8 * V[i][j];
						}



						

						if (j - 1 >= 0 && j - 1 <= 3 && j - 1 > 1) // left condition 
						{
				
							Q[i][j][a] += gamma * 0.1 * V[i][j - 1];

						}
						else
						{
							
							Q[i][j][a] += gamma * 0.1 * V[i][j];
						}



						if (j + 1 <= 3 && j + 1 >= 0 && j + 1 != 1) // right condition 
						{
						
							Q[i][j][a] += gamma * 0.1 * V[i][j + 1]; 

						}
						else
						{
							
							Q[i][j][a] += gamma * 0.1 * V[i][j]; 
						}



						if (Q[i][j][a] > maxQ)
						{
							maxQ = Q[i][j][a]; 
							maxQindex = a; 
						}
						break;












						
						
					case 1:
						//going down

						Q[i][j][a] = R[i][j];

						if (i - 1 <= 2 && i - 1 >= 0 && j != 1)
						{
							
							Q[i][j][a] += gamma * 0.8 * V[i - 1][j];
						}
						else
						{
						
							Q[i][j][a] += gamma * 0.8 * V[i][j];
						}

						
						if (j - 1 >= 0 && j - 1 <= 3 && j - 1 != 1) // checking the left condition 
						{
						
							Q[i][j][a] += gamma * 0.1 * V[i][j - 1];
						}
						else
						{
						
							Q[i][j][a] += gamma * 0.1 * V[i][j];
						}


						if (j + 1 <= 3 && j + 1 >= 1 &&  j+ 1 != 1) // checking the right condition  
						{
							
							Q[i][j][a] += gamma * 0.1 * V[i][j + 1];
						}
						else
						{
							
							Q[i][j][a] += gamma * 0.1 * V[i][j];
						}

						if (Q[i][j][a] > maxQ)
						{
							maxQ = Q[i][j][a];
							maxQindex = a;
						}
						break;












					case 2:
						//going left

						
						Q[i][j][a] = R[i][j];
						if  (j - 1 >= 0 && j - 1 <= 3 && i != 1)
						{
						
							Q[i][j][a] += gamma * 0.8 * V[i][j - 1];
						}
						else if(j - 1 >= 0 && j - 1 <= 3 && i == 1 && j - 1 > 1)
						{

							Q[i][j][a] += gamma * 0.8 * V[i][j - 1];

						}
						else
						{
							Q[i][j][a] += gamma * 0.8 * V[i][j];

						}

						

						if (i + 1 >= 0 && i + 1 <= 2 && j != 1 ) // checking for the up condition 
						{
							
							Q[i][j][a] += gamma * 0.1 * V[i + 1][j];
						}
						else
						{
							
							Q[i][j][a] += gamma * 0.1 * V[i][j];
						}



						if (i - 1 >= 0 && i - 1 <= 2 && j != 1)  // checking for the down condition 
						{
						
							Q[i][j][a] += gamma * 0.1 * V[i - 1][j];
						}
						else
						{
						
							Q[i][j][a] += gamma * 0.1 * V[i][j];
						}

						if (Q[i][j][a] > maxQ)
						{
							maxQ = Q[i][j][a];
							maxQindex = a;
						}
						break;







					case 3:
						//going right

						Q[i][j][a] = R[i][j]; // take the immediate reward 


						if (j + 1 >= 0 && j + 1 <= 3 && i != 1)
						{
							
							Q[i][j][a] = Q[i][j][a] + gamma * 0.8 * V[i][j + 1];
						}
						else if(j + 1 >= 0 && j + 1 <= 3 && i == 1 && j + 1 > 1)
						{

							Q[i][j][a] = Q[i][j][a] + gamma * 0.8 * V[i][j + 1];

						}
						else
							Q[i][j][a] += gamma * 0.8 * V[i][j];



						

						if (i + 1 >= 0 && i + 1 <= 2 && j != 1) // checking for the upper condition  
						{
							
							Q[i][j][a] += gamma * 0.1 * V[i + 1][j];
						}
						else 
						{
						
							Q[i][j][a] += gamma * 0.1 * V[i][j];
						}

						if (i - 1 >= 0 && i - 1 <= 2 && j != 1 ) // checking for the lower condition 
						{
							
							Q[i][j][a] += gamma * 0.1 * V[i - 1][j];
						}
						else
						{
						
							Q[i][j][a] += gamma * 0.1 * V[i][j];
						}

						if (Q[i][j][a] > maxQ)
						{
							maxQ = Q[i][j][a];
							maxQindex = a;
						}
						break;
						

					}


				}
				V[i][j] = maxQ; 
				Policy[i][j] = maxQindex; 



			}
		}



	}




}










int main()
{

	double gamma = 1.0; 
	
	 
	initializing_gridworld(); 
	 
	
	
	valueIteration(gamma );
	 printPolicy();

	cout << endl; 

	

	printV(); 
	

	
	

	

}