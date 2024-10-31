--Cursors: (All types: Implicit, Explicit, Cursor FOR Loop, Parameterized Cursor)
--Write a PL/SQL block of code using parameterized Cursor, that will merge the 
--data available in the newly created table N_EmpId with the data available in the table O_EmpId.
--If the data in the first table already exist in the second table then that data should be skipped.
-- Step 1: Create the "old" employee table


create table o_emp(
    e_id int,             -- Employee ID (integer)
    fname varchar(45),    -- First name (up to 45 characters)
    lname varchar(45),    -- Last name (up to 45 characters)
    salary int            -- Salary (integer)
);

-- Step 2: Create the "new" employee table
create table n_emp(
    e_id int primary key, -- Employee ID as a primary key to enforce uniqueness
    fname varchar(45),    -- First name (up to 45 characters)
    lname varchar(45),    -- Last name (up to 45 characters)
    salary int            -- Salary (integer)
);

-- Step 3: Insert data into the "old" employee table
insert into o_emp (e_id, fname, lname, salary)
values 
    (1, 'Ayush', 'B', 20000),
    (2, 'Piyush', 'Joih', 30000),
    (3, 'Kumar', 'Yadav', 34000),
    (4, 'Ash', 'M', 40000),
    (5, 'Ajey', 'N', 30000),
    (6, 'Yash', 'S', 40000);

-- Step 4: Create a procedure with a cursor to transfer data from o_emp to n_emp
delimiter $
drop procedure if exists copyData;
create procedure copyEmp() 
begin
    -- Step 4.1: Declare a variable to track the end of cursor
    declare done int default false;

    -- Step 4.2: Declare variables to store data fetched from the cursor
    declare n_e_id int;
    declare n_fname varchar(45);
    declare n_lname varchar(45);
    declare n_salary int;

    -- Step 4.3: Define a cursor to select all rows from the "old" employee table (o_emp)
    declare cur cursor for 
        select e_id, fname, lname, salary from o_emp;

    -- Step 4.4: Declare a handler to set `done` to true when no more rows are found
    declare continue handler for not found set done = true;

    -- Step 4.5: Open the cursor to begin fetching data from o_emp
    open cur;

    -- Step 4.6: Begin the loop to read each row from o_emp
    read_loop : LOOP 
        -- Fetch the current row from the cursor into declared variables
        fetch cur into n_e_id, n_fname, n_lname, n_salary;

        -- Check if the cursor has reached the end of the table
        if done then 
            leave read_loop; -- Exit the loop if no more rows
        end if;

        -- Step 4.7: Check if the current employee ID already exists in n_emp
        if not exists(select 1 from n_emp where n_emp.e_id = n_e_id) then 
            -- If the employee ID is not found in n_emp, insert the row
            insert into n_emp(e_id, fname, lname, salary) 
            values(n_e_id, n_fname, n_lname, n_salary);
        end if;
    end loop;

    -- Step 4.8: Close the cursor after processing all rows
    close cur;
end;
$
DELIMITER ;

-- Step 5: Call the procedure to execute the data transfer
call copyEmp();

-- Step 6: Check the data in n_emp to verify that records were transferred correctly
select * from n_emp;
