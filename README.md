# 🍰 Patisserie Management System (C++ Project)

This project simulates the management of a patisserie, handling everything from employees and jobs to recipes, suppliers, and production steps. It is written in **C++** and uses a collection of structured text files as its database.

---

## 📂 Data Files

The system loads and processes information from the following files:

- **`angajati.txt`** — Employee details: personal data, contact info, languages spoken.
- **`joburi.txt`** — Job hierarchy, salaries, and roles (owner, manager, chefs, assistants, marketing, IT, etc.).
- **`departamente.txt`** — Departments: management, kitchen, customer relations, maintenance.
- **`CV_angajari.txt`** — Applicants’ CVs for new hiring simulations.
- **`ingrediente.txt`** — Ingredients, utensils, packaging, and stock levels.
- **`retete.txt`** — Recipes for cakes and pastries, including ingredients and quantities.
- **`tip_produse.txt`** — Categories of products (cakes, pastries).
- **`furnizori.txt`** — Suppliers (Boromir, Albalact, Dr.Oetker, Metro, Ecofruct, etc.).
- **`etape_de_productie.txt`** — Production workflow steps (preparation, baking, decorating, packaging, delivery).
- **`date_login.txt`** — User credentials for logging into the system.
- **`main.cpp`** — Source code of the project.

---

## 🔑 Logging In

Login is handled through **`date_login.txt`**, which contains valid username-password pairs:

```
manager123 blabla
owner456   cracra
```

To access the system:
1. Run the program (`./proiect`).
2. Enter a username and password when prompted.
   - Example login as manager:
     ```
     Username: manager123
     Password: blabla
     ```
   - Example login as owner:
     ```
     Username: owner456
     Password: cracra
     ```
3. After login, the system will load the appropriate permissions and allow you to interact with data (employees, jobs, recipes, suppliers, etc.).

---

## ⚙️ Building

Make sure you have a C++ compiler (e.g., `g++`) installed. To compile:

```bash
g++ -std=c++17 -o proiect main.cpp
```

Then run:

```bash
./proiect
```

---

## ▶️ Features

- **Authentication system** (manager / owner accounts).
- **Employee management** — View employees, roles, departments, and languages spoken.
- **Hiring simulation** — Parse CVs and suggest possible hires.
- **Suppliers & ingredients** — Manage inventory and source ingredients from suppliers.
- **Recipe management** — Load and display recipes for cakes and pastries.
- **Production pipeline** — Step-by-step workflow from recipe setup to packaging and delivery.
