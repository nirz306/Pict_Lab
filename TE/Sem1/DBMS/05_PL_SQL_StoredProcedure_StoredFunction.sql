create table stud_marks(
    id int primary key auto_increment,
    roll int,
    name varchar(30),
    total_marks int
);


-- // --2. Create table result
create table result(
    roll int,
    name varchar(30),
    class varchar(30)
);


-- // --3. Insert Data into stud_marks;
insert into stud_marks(roll, name, total_marks)
values (1, "Ayush", 1488),
    (2, "Piysh", 1300),
    (3, "Karan", 980),
    (4, "Ajey", 970),
    (5, "Yash", 857),
    (6, "David", 845);

-- // -- 4. Create a PROCEDURE to calculate the grades
DELIMITER #
DROP PROCEDURE IF EXISTS proc_result;
CREATE PROCEDURE proc_result(IN marks INT, OUT class CHAR(20)) 
BEGIN 
    IF marks BETWEEN 991 AND 1500 THEN
        SET class = 'Distinction';
    ELSEIF marks BETWEEN 891 AND 990 THEN
        SET class = 'First Class';
    ELSEIF marks BETWEEN 826 AND 890 THEN
        SET class = 'Higher Second Class';
    ELSEIF marks BETWEEN 751 AND 825 THEN
        SET class = 'Second Class';
    ELSEIF marks BETWEEN 651 AND 750 THEN
        SET class = 'Passed';
    ELSE
        SET class = 'Fail';
    END IF;
END #

DELIMITER ;

DELIMITER #
DROP FUNCTION IF EXISTS final_result;
CREATE FUNCTION final_result(rno INT) RETURNS INT DETERMINISTIC 
BEGIN
    DECLARE fmarks INT;
    DECLARE grade VARCHAR(30);
    DECLARE stud_name VARCHAR(30);

    -- Continue handler for not found
    DECLARE CONTINUE HANDLER FOR NOT FOUND 
    BEGIN 
        RETURN 0; 
    END;

    -- Select total marks and name from stud_marks
    SELECT sm.total_marks, sm.name INTO fmarks, stud_name
    FROM stud_marks AS sm
    WHERE sm.rollno = rno;

    -- If no record is found, it will go to the handler
    IF fmarks IS NULL THEN
        RETURN 0; -- Return 0 if no record found
    END IF;

    -- Call the procedure to get the grade
    CALL proc_result(fmarks, grade);
    
    -- Insert the result into the result table
    INSERT INTO result(roll, name, class)
    VALUES(rno, stud_name, grade);

    RETURN rno; -- Return the roll number of the student
END #
DELIMITER ;

select * from result;

SELECT final_result(1);
SELECT final_result(2);
SELECT final_result(3);
SELECT final_result(4);
SELECT final_result(5);
SELECT final_result(6);

DESCRIBE stud_marks;
