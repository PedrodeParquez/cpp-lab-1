#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class Athlete {
public:
  string lastName;
  int birthYear;
  double resultJump;

  Athlete(string lastName, int birthYear, double jumpDistance);
};

Athlete::Athlete(string lastName, int birthYear, double resultJump)
  : lastName(lastName),
  birthYear(birthYear),
  resultJump(resultJump) {

}

vector<Athlete> readTextFile(const string& filename);

void mathematics();

void athletesRank();

void athletesChoice();

void athletesAddToFile();

bool isAlphaString(const string& str);

void appendAthleteToFile(const string& filename, const Athlete& athlete);


int main() {
  int numberTask;
  setlocale(LC_ALL, "Russian");

  cout << "Введите номер упражнения: ";
  cin >> numberTask;

  switch (numberTask) {
  case 1:
    mathematics();
    break;
  case 2:
    athletesChoice();
    break;
  default:
    cout << "Некорректный ввод! Повтороно введите номер задачи.";
    main();
  }
}

void mathematics() {
  double a, b, x2, y2;

  cout << "Пожалуйста, введите x2: ";
  cin >> x2;

  while (cin.fail()) {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Некорректный ввод! Повторите попытку заново!\n"
         << "Пожалуйста, введите x2: ";
    cin >> x2;
  }

  cout << "Пожалуйста, введите коэффициент a: ";
  cin >> a;

  while (cin.fail()) {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Некорректный ввод! Повторите попытку заново!\n"
         << "Пожалуйста, введите a: ";
    cin >> a;
  }

  cout << "Пожалуйста, введите коэффициент b: ";
  cin >> b;

  while (cin.fail()) {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Некорректный ввод! Повторите попытку заново!\n"
         << "Пожалуйста, введите b: ";
    cin >> b;
  }
  
  y2 = a * x2 + b;

  cout << "Ордината точки O2 равна: " << fixed << setprecision(2) << y2;
 
}

void athletesRank() {
  int searchYear;
  vector<Athlete> matchingAthletes;

  string filename = "AthletesData.txt";

  vector<Athlete> athletes = readTextFile(filename);

  cout << "Введите год рождения для поиска: ";
  cin >> searchYear;

  while (cin.fail()) {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Некорректный ввод! Повторите попытку заново!\n"
         << "Пожалуйста, введите год рождения для поиска : ";
    cin >> searchYear;
  }

  for (const Athlete& athlete : athletes) {
    if (athlete.birthYear == searchYear) {
      matchingAthletes.push_back(athlete);
    }
  }

  if (!matchingAthletes.empty()) {
    auto bestAthlete = max_element(matchingAthletes.begin(), matchingAthletes.end(),
      [](const Athlete& a, const Athlete& b) {
        return a.resultJump < b.resultJump;
      });

    cout << "Спортсмен, родившийся в " << searchYear << " году, с лучшим результатом:\n";
    cout << "Фамилия: " << bestAthlete->lastName << "\n";
    cout << "Результат: " << bestAthlete->resultJump << " метра\n";
  }
  else {
    cout << "Спортсменов, родившихся в " << searchYear << " году, не найдено.\n";
    athletesRank();
  }
}

void athletesChoice() {
  int choice;

  cout << "Если вы хотите найти лучший результат - 1\n"
       << "Если хотите добавить нового ученика - 2\n"\
       << "Ваш выбор: ";
  cin >> choice;

  switch (choice) {
    case 1:
      athletesRank();
      break;
    case 2:
      athletesAddToFile();
      break;
    default:
      cout << "Некорректный ввод! Повтороно введите номер задачи.";
      athletesChoice();
  }
}

void athletesAddToFile() {
  string lastName;
  int birthYear;
  double resultJump;

  cout << "Введите фамилию спортсмена: ";
  cin >> lastName;  

  while (!isAlphaString(lastName)) {
    cout << "Фамилия должна содержать только буквы. Пожалуйста, введите фамилию спортсмена: ";
    cin >> lastName;
  }

  cout << "Введите год рождения спортсмена: ";
  cin >> birthYear;

  if (birthYear <= 0) {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Некорректный ввод! Повторите попытку заново!\n"
         << "Пожалуйста, введите год рождения спортсмена: ";
    cin >> birthYear;
  }

  while (cin.fail()) {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Некорректный ввод! Повторите попытку заново!\n"
         << "Пожалуйста, введите год рождения спортсмена: ";
    cin >> birthYear;
  }

  cout << "Введите результат прыжка спортсмена: ";
  cin >> resultJump;

  while (cin.fail()) {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Некорректный ввод! Повторите попытку заново!\n"
      << "Пожалуйста, введите результат прыжка спортсмена: ";
    cin >> resultJump;
  }

  Athlete newAthlete(lastName, birthYear, resultJump);
  appendAthleteToFile("AthletesData.txt", newAthlete);
  cout << "Спортсмен успешно добавлен в файл." << endl;
}

bool isAlphaString(const string& str) {
  for (char c : str) {
    if (!isalpha(c)) {
      return false;
    }
  }
  return true;
}

void appendAthleteToFile(const string& filename, const Athlete& athlete) {
  ofstream file(filename, ios::app);

  if (!file.is_open()) {
    cerr << "Ошибка при открытии файла для записи" << endl;
    return;
  }

  file << athlete.lastName << " " << athlete.birthYear << " " << athlete.resultJump << endl;
  file.close();
}

vector <Athlete> readTextFile(const string& filename) {
  vector <Athlete> athletes;
  ifstream file(filename);

  if (!file.is_open()) {
    cerr << "Ошибка при открытии файла для чтения" << endl;
    return athletes;
  }

  string line;

  while (getline(file, line)) {
    istringstream iss(line);
    std::string lastName;
    int birthYear;
    double resultJump;

    if (iss >> lastName >> birthYear >> resultJump) {
      Athlete athlete(lastName, birthYear, resultJump);
      athletes.push_back(athlete);
    }
  }

  file.close();

  return athletes;
}

//Переделать условие для первой задачи
