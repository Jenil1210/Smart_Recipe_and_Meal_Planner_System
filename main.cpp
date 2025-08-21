#include <bits/stdc++.h>
using namespace std;

struct Recipe {
    string name;
    vector<string> ingredients;
    int calories;
    string category;
};


vector<Recipe> loadRecipes() {
    vector<Recipe> recipes;
    ifstream file("file.csv");
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        Recipe r;
        string temp;
        getline(ss, r.name, ',');
        getline(ss, temp, ',');
        int n = stoi(temp);
        for (int i = 0; i < n; i++) {
            string ing;
            getline(ss, ing, ',');
            r.ingredients.push_back(ing);
        }
        getline(ss, temp, ',');
        r.calories = stoi(temp);
        getline(ss, r.category, ',');
        recipes.push_back(r);
    }
    return recipes;
}


void saveRecipes(const vector<Recipe>& recipes) {
    ofstream file("file.csv", ios::trunc); 
    for (auto &r : recipes) {
        file << r.name << "," << r.ingredients.size() << ",";
        for (auto &ing : r.ingredients) file << ing << ",";
        file << r.calories << "," << r.category << "\n";
    }
}

void addRecipe() {
    Recipe r;
    cout << "Enter recipe name: ";
    cin >> r.name;
    int n;
    cout << "Enter number of ingredients: ";
    cin >> n;
    r.ingredients.resize(n);
    for (int i = 0; i < n; i++) {
        cout << "Enter ingredient " << i+1 << ": ";
        cin >> r.ingredients[i];
    }
    cout << "Enter calories: ";
    cin >> r.calories;
    cout << "Enter category: ";
    cin >> r.category;

    auto recipes = loadRecipes();
    recipes.push_back(r);
    saveRecipes(recipes);

    cout << "Recipe added successfully!\n";
}


void displayAll() {
    auto recipes = loadRecipes();
    for (auto &r : recipes) {
        cout << "Recipe name: " << r.name << " Ingredients: ";
        for (auto &ing : r.ingredients) cout << ing << " ";
        cout << "Calories: " << r.calories << " Category: " << r.category << "\n";
    }
}

void searchByIngredient(string ing) {
    auto recipes = loadRecipes();
    for (auto &r : recipes) {
        if (find(r.ingredients.begin(), r.ingredients.end(), ing) != r.ingredients.end()) {
            cout << "Recipe: " << r.name << " contains " << ing << "\n";
        }
    }
}


void searchByCategory(string cat) {
    auto recipes = loadRecipes();
    for (auto &r : recipes) {
        if (r.category == cat) {
            cout << "Recipe: " << r.name << " (" << r.calories << " cal)\n";
        }
    }
}


void recipeDetails(string name) {
    auto recipes = loadRecipes();
    for (auto &r : recipes) {
        if (r.name == name) {
            cout << "Recipe: " << r.name << "\nIngredients: ";
            for (auto &ing : r.ingredients) cout << ing << ", ";
            cout << "\nCalories: " << r.calories << " Category: " << r.category << "\n";
            return;
        }
    }
    cout << "Recipe not found!\n";
}

void mealByCaloriesAndCategory(int maxCal, string cat) {
    auto recipes = loadRecipes();
    for (auto &r : recipes) {
        if (r.calories <= maxCal && r.category == cat) {
            cout << "Meal option: " << r.name << " (" << r.calories << " cal)\n";
        }
    }
}

void mealPlanner() {
    string b, l, d;
    cout << "Enter breakfast, lunch, dinner recipe names: ";
    cin >> b >> l >> d;
    cout << "\nBreakfast:\n"; recipeDetails(b);
    cout << "\nLunch:\n"; recipeDetails(l);
    cout << "\nDinner:\n"; recipeDetails(d);
}

void removeRecipe(string name) {
    auto recipes = loadRecipes();
    bool found = false;
    vector<Recipe> updated;
    for (auto &r : recipes) {
        if (r.name != name) updated.push_back(r);
        else found = true;
    }
    if (!found) {
        cout << "Recipe not found, nothing removed.\n";
        return;
    }
    saveRecipes(updated);
    cout << "Recipe removed successfully!\n";
}

void editRecipe(string name) {
    auto recipes = loadRecipes();
    bool found = false;
    for (auto &r : recipes) {
        if (r.name == name) {
            found = true;
            cout << "Editing " << r.name << "\n";

            while (true) {
                cout << "\nChoose what to edit:\n";
                cout << "1. Name\n2. Ingredients\n3. Calories\n4. Category\n0. Save & Exit\n";
                cout << "Enter choice: ";
                int choice; cin >> choice;

                if (choice == 0) break;  
                else if (choice == 1) {
                    cout << "Enter new name: ";
                    cin >> r.name;
                } 
                else if (choice == 2) {
                    int n;
                    cout << "Enter new number of ingredients: ";
                    cin >> n;
                    r.ingredients.resize(n);
                    for (int i = 0; i < n; i++) {
                        cout << "Enter ingredient " << i+1 << ": ";
                        cin >> r.ingredients[i];
                    }
                } 
                else if (choice == 3) {
                    cout << "Enter new calories: ";
                    cin >> r.calories;
                } 
                else if (choice == 4) {
                    cout << "Enter new category: ";
                    cin >> r.category;
                } 
                else {
                    cout << "Invalid choice!\n";
                }
            }
            break; 
        }
    }

    if (!found) {
        cout << "Recipe not found!\n";
        return;
    }

    saveRecipes(recipes);
    cout << "Recipe updated successfully!\n";
}

/
int main() {
    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Add recipe\n2. Display all\n3. Search by ingredient\n4. Search by category\n";
        cout << "5. Recipe details\n6. Meal by calories & category\n7. 3-meal planner\n";
        cout << "8. Remove recipe\n9. Edit recipe\n0. Exit\n";
        cout << "Enter choice: ";
        int n; cin >> n;
        if (n == 0) break;
        else if (n == 1) addRecipe();
        else if (n == 2) displayAll();
        else if (n == 3) {
            string ing; cout << "Enter ingredient: "; cin >> ing;
            searchByIngredient(ing);
        }
        else if (n == 4) {
            string cat; cout << "Enter category: "; cin >> cat;
            searchByCategory(cat);
        }
        else if (n == 5) {
            string name; cout << "Enter recipe name: "; cin >> name;
            recipeDetails(name);
        }
        else if (n == 6) {
            int cal; string cat;
            cout << "Enter max calories and category: ";
            cin >> cal >> cat;
            mealByCaloriesAndCategory(cal, cat);
        }
        else if (n == 7) mealPlanner();
        else if (n == 8) {
            string name; cout << "Enter recipe name to remove: "; cin >> name;
            removeRecipe(name);
        }
        else if (n == 9) {
            string name; cout << "Enter recipe name to edit: "; cin >> name;
            editRecipe(name);
        }
        else cout << "Invalid choice!\n";
    }
}
