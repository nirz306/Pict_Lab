--Cursors: (All types: Implicit, Explicit, Cursor FOR Loop, Parameterized Cursor)
--Write a PL/SQL block of code using parameterized Cursor, that will merge the 
--data available in the newly created table N_EmpId with the data available in the table O_EmpId.
--If the data in the first table already exist in the second table then that data should be skipped.
-- Step 1: Create the "old" employee table


drop table  if exists o_emp;
create table o_emp(
    e_id int,
    fname varchar(45),
    lname varchar(45),
    salary int
);
-- 2. create new table
drop table  if exists n_emp;
create table n_emp(
    e_id int,
    fname varchar(45),
    lname varchar(45),
    salary int
);
 

INSERT INTO o_emp (e_id, fname, lname, salary)
VALUES 
    (1, 'Ayush', 'B', 20000),
    (2, 'Piyush', 'Joih', 30000),
    (3, 'Kumar', 'Yadav', 34000),
	 (4, 'Ash', 'M', 40000),
    (5, 'Ajey', 'N', 30000),
    (6, 'Yash', 'S', 40000),
    (7, 'Ankit', 'Sharma', 25000),
    (8, 'Rohit', 'Verma', 36000),
    (9, 'Neha', 'Singh', 28000),
    (10, 'Sneha', 'Patil', 45000);
    
select * from o_emp;


    
    
    INSERT INTO n_emp (e_id, fname, lname, salary)
VALUES 
    (1, 'Ayush', 'B', 20000),         -- Same as in o_emp
    (3, 'Kumar', 'Yadav', 34000),     -- Same as in o_emp
    (5, 'Ajey', 'N', 30000),          -- Same as in o_emp
    (7, 'Ankit', 'Sharma', 25000),    -- Same as in o_emp
    (11, 'Raj', 'Kumar', 32000),      -- Unique entry
    (12, 'Anjali', 'Mehta', 29000),   -- Unique entry
    (13, 'Vikas', 'Desai', 37000),    -- Unique entry
    (14, 'Snehal', 'Pawar', 45000),   -- Unique entry
    (15, 'Ravi', 'Patel', 31000),     -- Unique entry
    (16, 'Priya', 'Nair', 33000);     -- Unique entry

    

  
-- Step 4: Create a procedure with a cursor to transfer data from o_emp to n_emp
delimiter $
drop procedure if exists copyEmp;
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
select * from n_emp;
-- | e_id | fname   | lname   | salary |
-- |------|---------|---------|--------|
-- | 1    | Ayush   | B       | 20000  |
-- | 3    | Kumar   | Yadav   | 34000  |
-- | 5    | Ajey    | N       | 30000  |
-- | 7    | Ankit   | Sharma  | 25000  |
-- | 11   | Raj     | Kumar   | 32000  |
-- | 12   | Anjali  | Mehta   | 29000  |
-- | 13   | Vikas   | Desai   | 37000  |
-- | 14   | Snehal  | Pawar   | 45000  |
-- | 15   | Ravi    | Patel   | 31000  |
-- | 16   | Priya   | Nair    | 33000  |
-- | 2    | Piyush  | Joih    | 30000  |
-- | 4    | Ash     | M       | 40000  |
-- | 6    | Yash    | S       | 40000  |
-- | 8    | Rohit   | Verma   | 36000  |
-- | 9    | Neha    | Singh   | 28000  |
-- | 10   | Sneha   | Patil   | 45000  |



-- merges the table only between the uper and lower bounds 
DELIMITER $
DROP PROCEDURE IF EXISTS mergeEMPwithinBounds;
CREATE PROCEDURE mergeEMPwithinBounds(IN lb INT, IN ub INT)
BEGIN
    DECLARE done INT DEFAULT 0;
    DECLARE eno INT;
    DECLARE old_cursor1 CURSOR FOR 
        SELECT e_id FROM o_emp WHERE e_id BETWEEN lb AND ub;
    DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = TRUE;
    
    OPEN old_cursor1;
    
    getE_id: LOOP
        IF done THEN
            LEAVE getE_id;
        END IF;
        
        FETCH old_cursor1 INTO eno;
        
        IF NOT EXISTS (SELECT 1 FROM n_emp WHERE e_id = eno) THEN 
            BEGIN
                INSERT INTO n_emp
                SELECT * FROM o_emp
                WHERE o_emp.e_id = eno;
            END;
        END IF;
    END LOOP;
    
    CLOSE old_cursor1;
END $
DELIMITER ;

-- Execute the procedure with bounds
CALL mergeEMPwithinBounds(1, 4);


select * from n_emp;
-- | e_id | fname   | lname   | salary |
-- |------|---------|---------|--------|
-- | 1    | Ayush   | B       | 20000  |
-- | 3    | Kumar   | Yadav   | 34000  |
-- | 5    | Ajey    | N       | 30000  |
-- | 7    | Ankit   | Sharma  | 25000  |
-- | 11   | Raj     | Kumar   | 32000  |
-- | 12   | Anjali  | Mehta   | 29000  |
-- | 13   | Vikas   | Desai   | 37000  |
-- | 14   | Snehal  | Pawar   | 45000  |
-- | 15   | Ravi    | Patel   | 31000  |
-- | 16   | Priya   | Nair    | 33000  |
-- | 2    | Piyush  | Joih    | 30000  |
-- | 4    | Ash     | M       | 40000  |
