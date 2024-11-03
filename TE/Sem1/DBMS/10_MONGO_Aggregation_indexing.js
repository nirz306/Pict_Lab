/*
 Practical No 10: MongoDB Aggregation and Indexing: Design and Develop MongoDB Queries using aggregation and
 indexing with suitable example using MongoDB

 Schema:
 {
    "product":"Toothbrush",
    "price":22,
    "customer":"Ayush"
 }

 Queries to solve:
    1.Find out how many toothbrushes were sold
    2.Find the list of all sold products
    3.Find the total amount of money spent by each customer
    4.Find how much has been spent on each product and sort it by amount spent
    5.Find the product with least earnings.
    6.Find how much money each customer has spent on toothbrushes and pizza
    7.Find the customer who has given highest business for the product toothbrush
*/

// 1. Create collection.

db.createCollection("orders");


//2. Insert Documents
db.orders.insertMany([
    {
        "product": "toothbrush",
        "price": 21,
        "customer": "Ayush"
    },
    {
        "product": "toothbrush",
        "price": 21,
        "customer": "Durvesh"
    },
    {
        "product": "pizza",
        "price": 130,
        "customer": "Kushal"
    },
    {
        "product": "pizza",
        "price": 130,
        "customer": "Ayush"
    },
    {
        "product": "tea",
        "price": 20,
        "customer": "Karan"
    },
    {
        "product": "tea",
        "price": 20,
        "customer": "Yash"
    }
]);



//1. Find out how many toothbrushes were sold
//Single Aggregation
//Each document that matches the criteria contributes 1 to the sum
db.orders.aggregate([
    {
        $match: { product: 'toothbrush' }
    },
    {
        $group: {
            _id: "$product",
            totalQty: { $sum: 1 }
        }
    }
]);
//  output : [ { _id: 'toothbrush', totalQty: 4 } ]

//2. Find the list of all products sold
db.orders.distinct("product");
//OR
db.orders.aggregate([
    {
        $group: {
            _id: "$product"
        }
    }   
]);


//3. Find the total amount of money spent by each customer
db.orders.aggregate([
    {
        $group: {
            _id: "$customer",
            totalSpending: { $sum: "$price" }
        }
    }
])




// 4.Find how much has been spent on each product and sort it by amount spent

db.orders.aggregate([
    {
        $group: {
            _id: "$product",
            totalSpent: { $sum: "$price" }
        }
    },
    {
        $sort: {
            totalSpent: -1
        }
    }
])

// 5.Find the product with least earnings.
db.orders.aggregate([
    {
        $group: {
            _id: "$product",
            earnings: { $sum: "$price" }
        }
    },
    {
        $sort: {
            price: 1
        }
    },
    {
        $limit: 1 //top ekch ele ghenar 
    }
])

// 6.Find how much money each customer has spent on toothbrushes and pizza

db.orders.aggregate([
    {
        $match: { product: { $in: ['toothbrush', 'pizza'] } }
    },
    {
        $group: {
            _id: "$customer",
            spending: { $sum: "$price" }
        }
    }
])


// 7.Find the customer who has given highest business for the product toothbrush
db.orders.aggregate([
    {
        $match: { product: 'toothbrush' }
    },
    {
        $group: {
            _id: "$customer",
            bussiness: { $sum: "$price" }
        }
    },
    {
        $sort: { bussiness: -1 }
    },
    {
        $limit: 1
    }
])


//this is different schema (prev ques) however the use of unwind is imp 
teachers.aggregate([ { $unwind: "$qualification" }, { $group: { _id: "$qualification", teacherCount: { $sum: 1 } } }] )
// [
//   { _id: 'MTech', teacherCount: 6 },
//   { _id: 'PhD', teacherCount: 10 },
//   { _id: 'BTech', teacherCount: 1 }
// ]
