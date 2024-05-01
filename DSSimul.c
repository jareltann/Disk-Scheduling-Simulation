#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TRACKS 200

void sstf(int* request, int head, int n){


	int servicedOrder[n];
	int tracksTraversed = 0;
	int currentTrack = head;


	// Array to keep track of whether a request has been serviced
	int serviced[n];
	for (int i=0; i<n; i++){
		serviced[i] = 0;
	}

	for (int i=0; i<n; i++){
		int minDistance = TRACKS + 1;
		int minIndex = -1;

		for (int j=0; j<n; j++){
			if (!serviced[j]){
				int distance = abs(currentTrack - request[j]);
				if (distance < minDistance){
					minDistance = distance;
					minIndex = j;
				}
			}
		}


		// Mark the selected request as serviced
		serviced[minIndex] = 1;

		// Update the total tracks traversed
		tracksTraversed += minDistance;

		// Update the current track
		currentTrack = request[minIndex];

		// Store the serviced track in the order
		servicedOrder[i] = currentTrack;
	}


	// Print the order of the original request list
	printf("Order of the original list for SSTF: ");
	for (int i=0; i<n; i++){
		printf("%d ", request[i]);
	}

	// Print the order of serviced tracks
	printf("\nOrder of serviced tracks from SSTF: ");
	for (int i=0; i<n; i++){
		printf("%d ", servicedOrder[i]);
	}

	// Print the total tracks traversed
	printf("\nTotal tracks traversed for SSTF: %d\n", tracksTraversed);


	// Calculate the longest delay
	int longestDelay = 0;
	int totalDelay = 0;
	int numDelayedTracks = 0;

	for (int i=0; i<n; i++){
		for (int j=0; j<n; j++){
			if (request[i] == servicedOrder[j] && j>i){
				int cur_delay = j-i;
				totalDelay += cur_delay;
				numDelayedTracks++;
				if (cur_delay > longestDelay){
					longestDelay = cur_delay;
				}
			}
		}
	}



	printf("Longest delay for SSTF: %d\n", longestDelay);


	// Calculate the average delay
	if (numDelayedTracks > 0){
		printf("Average delay for SSTF: %.2f\n", (float)totalDelay/numDelayedTracks);
	}
	else{
		printf("Average delay for SSTF: 0\n");
	}

}



void scan(int* request, int head, int n){

        // Array to keep track of whether a request has been serviced
        int serviced[n];
        for (int i=0; i<n; i++){
                serviced[i] = 0;
        }


	int sortedArray[n];
	for (int i=0; i<n; i++){
		sortedArray[i] = request[i];
	}

	int temp;
	for (int i=0; i<n-1; i++){
		for (int j=0; j<n-i-1; j++){
			if (sortedArray[j] > sortedArray[j+1]){
				temp = sortedArray[j];
				sortedArray[j] = sortedArray[j+1];
				sortedArray[j+1] = temp;
			}
		}
	}


	// Find the index of the current track (head) in the sorted list
	int currentTrack = head;
	int currentIndex = 0;
	for (int i=0; i<n; i++){
		if (sortedArray[i] >= currentTrack){
			currentIndex = i;
			break;
		}
	}


	// Scan algorithm: moving towards (left) lower track numbers
//	int totalDelay = 0;
	int tracksTraversed = 0;
	int scanOrder[n];
	int scanOrderIndex = 0;
	int count = 0;

	for (int i=currentIndex; i>=0; i--){
		if (!serviced[i]){
			tracksTraversed += abs(sortedArray[i] - currentTrack);
			currentTrack = sortedArray[i];
			scanOrder[scanOrderIndex] = currentTrack;
			scanOrderIndex++;
			count++;
		}
		serviced[i] = 1;

		if (i==0 && currentTrack != 0 && count != n){
			tracksTraversed += currentTrack;
		}
	}

if (count == n){

        printf("Order of the original list for SCAN: ");
        for (int i=0; i<n; i++){
                printf("%d ", request[i]);
        }


        // Print the order of serviced tracks
        printf("\nOrder of serviced tracks for SCAN: ");
        for (int i=0; i<n; i++){
                printf("%d ", scanOrder[i]);
        }

        // Print the total tracks traversed
        printf("\nTotal tracks traversed for SCAN: %d\n", tracksTraversed);


}

else{

	for (int i=0; i<n; i++){
		if (!serviced[i]){
	                tracksTraversed += abs(sortedArray[i] - currentTrack);
	                currentTrack = sortedArray[i];
			scanOrder[i] = currentTrack;
			scanOrderIndex++;
		}
		serviced[i] = 1;

                if (i==0 && currentTrack != 0){
                        tracksTraversed += currentTrack;
                }

        }


        // Print the order of the original request list
        printf("Order of the original list for SCAN: ");
        for (int i=0; i<n; i++){
                printf("%d ", request[i]);
        }

        // Print the order of serviced tracks
        printf("\nOrder of serviced tracks for SCAN: ");
        for (int i=0; i<n; i++){
                printf("%d ", scanOrder[i]);
        }

        // Print the total tracks traversed
        printf("\nTotal tracks traversed for SCAN: %d\n", tracksTraversed);
}

        // Calculate the longest delay
        int longestDelay = 0;
        int totalDelay = 0;
        int numDelayedTracks = 0;

        for (int i=0; i<n; i++){
                for (int j=0; j<n; j++){
                        if (request[i] == scanOrder[j] && j>i){
                                int cur_delay = j-i;
                                totalDelay += cur_delay;
                                numDelayedTracks++;
                                if (cur_delay > longestDelay){
                                        longestDelay = cur_delay;
                                }
                        }
                }
        }

        printf("Longest delay for SCAN: %d\n", longestDelay);


        // Calculate the average delay
        if (numDelayedTracks > 0){
                printf("Average delay for SCAN: %.2f\n", (float)totalDelay/numDelayedTracks);
        }
        else{
                printf("Average delay for SCAN: 0\n");
        }



}


int main(int argc, char* argv[]){

int n;
int* request;
int head;

// Check if a command-line argument is provided
if (argc > 1){

	char* str = argv[1];
	int length = strlen(argv[1]);
	n = 1; // to count for one extra item since #commas = n-1

	for (int i=0; i<length; i++){
		if (str[i] == ','){
			n++;
		}
	}

	// Allocate memory for the request list
	request = malloc(n*sizeof(int));

	// Parse the track numbers and store in the request list
	char* token = strtok(argv[1], ",");


	for (int i=0; i<n; i++){
		request[i] = atoi(token);
		token = strtok(NULL,",");
	}


}


else{

	srand(time(NULL));
	n = 50;

	// Allocate memory
	request = malloc(n*sizeof(int));

	int k,i;
        for (i=0; i<n; i++){
                int temp = rand() % TRACKS;
                for (k=0; k<i; k++){
			if (temp == request[k]){
				break;
			}
		}
		if (i==k){
			request[i]=temp;
		}
		else{
			i--;
		}
	}

}


	head = request[0];

	sstf(request,head,n);

	scan(request,head,n);

	free(request);


	return 0;

}
