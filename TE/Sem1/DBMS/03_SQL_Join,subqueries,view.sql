-- SQL Queries all types of Join, Sub-Query and View:
-- Write at least10 SQL queries for suitable database application using SQL DML statements

-- Find Employee details and Department details using NATURAL JOIN. 
    -- 2. Find the emp_fname,Emp_position,location,Emp_JoinDate who have same Dept id. 
-- 3. Find the Employee details ,Proj_id,Project cost who does not have Project location as ‘Hyderabad’.
-- 4. Find Department Name ,employee name, Emp_position for which project year is 2020,
-- 5. Display emp_position,D_name who have Project cost >30000
-- 6. Find the names of all the Projects that started in the year 2015.
-- 7. List the Dept_name having no_of_emp=10 
-- 8.Display the total number of employee who have joined any project before 2009
-- 9. Create a view showing the employee and Department details. 
-- 10. Perform Manipulation on simple view-Insert, update, delete, drop view.


--  1. Find Employee details and Department details using NATURAL JOIN.
select *
from employee
    inner join dept
where employee.dept_id = dept.dept_id;

--  2. Find the emp_fname,Emp_position,location,Emp_JoinDate who have same Dept id.
select e.emp_position,
    e.emp_join_date,
    d.dept_location
from employee as e,
    dept as d
where e.emp_id = d.dept_id
group by d.dept_id;
-- +-----------------------+---------------+---------------+
-- | emp_position          | emp_join_date | dept_location |
-- +-----------------------+---------------+---------------+
-- | Accountant            | 2021-10-02    | Mumbai        |
-- | HR Manager            | 2021-09-18    | Pune          |
-- | Software Engineer     | 2021-05-26    | Mumbai        |
-- | Marketing Coordinator | 2020-12-08    | Nashik        |
-- | Business Analyst      | 2021-07-27    | Nagpur        |
-- +-----------------------+---------------+---------------+
-- 5 rows in set (0.01 sec)

--  3. Find the Employee details ,Proj_id,Project cost who does not have Project location as ‘Hyderabad’.
SELECT DISTINCT e.emp_id, e.emp_fname, e.emp_lname, p.proj_id, p.proj_cost
FROM employee AS e
JOIN projects AS p ON e.dept_id = p.dept_id
WHERE p.proj_location <> 'Hyderabad';

--  4. Find Department Name ,employee name, Emp_position for which project year is 2020,
SELECT e.dept_id, e.emp_fname, e.emp_position, d.dept_name
FROM employee AS e
JOIN projects AS p ON e.dept_id = p.dept_id
JOIN dept AS d ON e.dept_id = d.dept_id
WHERE p.proj_year = 2022;

--  5. Display emp_position,D_name who have Project cost >30000
SELECT e.dept_id, e.emp_fname, e.emp_position, d.dept_name
FROM employee AS e
JOIN projects AS p ON e.dept_id = p.dept_id
JOIN dept AS d ON e.dept_id = d.dept_id
WHERE p.proj_cost>30000;

--  6. Find the names of all the Projects that started in the year 2015.
select proj_name
from projects
where proj_year>=2015;

--  7. List the Dept_name having no_of_emp=10
SELECT d.dept_name
FROM dept AS d
JOIN employee AS e ON d.dept_id = e.dept_id
GROUP BY d.dept_id
HAVING COUNT(e.emp_id) = 10;

--  8.Display the total number of employee who have joined any project before 2009
SELECT COUNT(DISTINCT e.emp_id) AS total_employees
FROM employee AS e
JOIN projects AS p ON e.dept_id = p.dept_id
WHERE p.proj_year < 2009;

--  9. Create a view showing the employee and Department details.
CREATE VIEW employee_department_view AS
SELECT e.emp_id, e.emp_fname, e.emp_lname, e.emp_position, e.emp_salary, e.emp_join_date, d.dept_name, d.dept_location
FROM employee AS e
JOIN dept AS d ON e.dept_id = d.dept_id;

-- 10. Perform Manipulation on simple view-Insert, update, delete, drop view
INSERT INTO employee_department_view (emp_fname, emp_lname, emp_position, emp_salary, emp_join_date, dept_name, dept_location)
VALUES ('John', 'Doe', 'Analyst', 600000, '2023-01-15', 'IT', 'Pune');

UPDATE employee_department_view
SET emp_salary = 700000
WHERE emp_id = 1;

DELETE FROM employee_department_view
WHERE emp_id = 1;

DROP VIEW employee_department_view;


