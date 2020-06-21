#include <iostream>
#include <string>
#include <stack>
using namespace std;

typedef struct adjacent_cities {

    int distance;
    int adj_index;
    adjacent_cities *next;

} adjacent_cities;

typedef struct city {

    string city_name;
    bool is_visited;
    adjacent_cities *adjacents_stack_head;

} city;

city *new_city_helper(string city_name) {

    city * new_city = (city *) malloc(sizeof(city));

    new_city->city_name = city_name;
    new_city->is_visited = 0;
    new_city->adjacents_stack_head = NULL;

    return new_city;

}

adjacent_cities * new_adjacent_helper (int distance, int index) {

    adjacent_cities * new_adjacent = (adjacent_cities *) malloc(sizeof(adjacent_cities));

    new_adjacent->distance = distance;
    new_adjacent->adj_index = index;
    new_adjacent->next = NULL;

    return new_adjacent;

}

void push_adjacent(city ** current_city, int adjacent_index, int adjacent_distance) {
    
    adjacent_cities * tmp = (*current_city)->adjacents_stack_head;

    (*current_city)->adjacents_stack_head = 
        new_adjacent_helper(adjacent_distance, adjacent_index);
    (*current_city)->adjacents_stack_head->next = tmp;

}

void dfs(city * city_list[], int current_index, int target_index, city ** cities_on_the_way, bool *found, int *distance_from_the_previous_city) {
    
    if (city_list[current_index]->is_visited) {
        return;
    }

    city_list[current_index]->is_visited = 1;

    if (current_index == target_index) {

        *found = true;
        push_adjacent(cities_on_the_way, current_index, *distance_from_the_previous_city);
        return;
    
    }

    adjacent_cities * head_ref = city_list[current_index]->adjacents_stack_head;

    while (head_ref != NULL) {
        
        dfs (city_list, head_ref->adj_index, target_index, &(*cities_on_the_way), found, &(head_ref->distance));
        
        if (*found) {

            push_adjacent(cities_on_the_way, current_index, *distance_from_the_previous_city);
            return;

        }

        head_ref = head_ref->next;

    }

}

int main() {

    city * city_list[] = {
    new_city_helper("Prague"),
    new_city_helper("London"),
    new_city_helper("Helsinki"),
    new_city_helper("Tokyo"),
    new_city_helper("Jakarta"),
    new_city_helper("New York"),
    new_city_helper("Beijing")};

    push_adjacent(&city_list[0], 1, 1264);
    push_adjacent(&city_list[0], 2, 1845);
    push_adjacent(&city_list[1], 3, 9566);
    push_adjacent(&city_list[2], 3, 7815);
    push_adjacent(&city_list[3], 4, 5782);
    push_adjacent(&city_list[3], 5, 10838);
    push_adjacent(&city_list[4], 6, 4616);
    push_adjacent(&city_list[5], 1, 5567);
    push_adjacent(&city_list[6], 1, 8132);
    push_adjacent(&city_list[6], 3, 1303);
    push_adjacent(&city_list[6], 5, 11550);

    city * cities_on_the_way = new_city_helper(" ");
    push_adjacent(&cities_on_the_way, 0, 0);

    bool found = false;
    int distance_from_the_previous_city = 0;
    int from, to, sum = 0;
    
    while(from < 0 || from > 6 || to < 0 || to > 6) {
        for(int i = 0; i < 7; i++){
            cout << i+1 << ". " << city_list[i]->city_name << endl;
        }
        cout << "From: (Please enter the number of one of the cities above)" << endl;
        cin >> from;
        cout << "To: (Please enter the number of one of the cities above)" << endl;
        cin >> to;
        from --; to --;
    }

    dfs(city_list, from, to, &cities_on_the_way, &found, &distance_from_the_previous_city);

    adjacent_cities * head = cities_on_the_way->adjacents_stack_head;

    if (head->next == NULL) {

        cout << "Path not found from " << city_list[from]->city_name << " to " << city_list[to]->city_name << endl;

    } else {

        cout << "Path found: "; 
        
        while (head->next != NULL) {

            cout << city_list[head->adj_index]->city_name;
            sum += head->distance;
            head = head->next;
            if (head->next != NULL)
                cout << ", ";
            else
                cout << endl;
    
        } 
        
        cout << "Total distance is " << sum << endl;

    }
  
    return 0;

}