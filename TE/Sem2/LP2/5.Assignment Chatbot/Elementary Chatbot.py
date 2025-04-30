from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.metrics.pairwise import cosine_similarity
import numpy as np
import re

# Menu Data with Price and Serving Info
menu = {
    "Espresso": {"price": "Rs 50.99", "serves": "1 person"},
    "Cappuccino": {"price": "Rs 70.49", "serves": "1 person"},
    "Latte": {"price": "Rs 80.99", "serves": "1 person"},
    "Black Coffee": {"price": "Rs 40.99", "serves": "1 person"},
    "Masala Chai": {"price": "Rs 30.99", "serves": "1 person"},
    "Green Tea": {"price": "Rs 35.49", "serves": "1 person"},
    "Iced Tea": {"price": "Rs 45.99", "serves": "1 person"},
    "Hot Chocolate": {"price": "Rs 90.49", "serves": "1 person"},
    "Fresh Lime Soda": {"price": "Rs 55.99", "serves": "1 person"},
    "Fruit Punch": {"price": "Rs 65.49", "serves": "1 person"},
    "Smoothie (Mango/Berry)": {"price": "Rs 85.99", "serves": "1 person"}
}

# Predefined Responses
data = [
    "Welcome to our café! We are open from 9 AM to 10 PM every day.",
    "We offer a variety of non-alcoholic beverages including Espresso, Cappuccino, and Latte.",
    "Our special drink is the Hot Chocolate.",
    "We provide home delivery within a 10-mile radius.",
    "Our café is located at 123 Beverage Lane, City Center.",
    "You can make a reservation by calling us at +1234567890 or through our website.",
    "We have refreshing beverages like Fresh Lime Soda and Iced Tea.",
    "We also offer healthy options such as Green Tea and Fruit Punch.",
    "We accept cash, credit/debit cards, and digital payments like Apple Pay and Google Pay.",
    "Outdoor seating is available, and we offer private event bookings."
]

# TF-IDF Setup
vectorizer = TfidfVectorizer()
tfidf_matrix = vectorizer.fit_transform(data)

# Get Best Match with TF-IDF
def get_best_response(user_input):
    """Returns the most relevant response using TF-IDF similarity."""
    user_vector = vectorizer.transform([user_input])
    similarities = cosine_similarity(user_vector, tfidf_matrix)
    best_match_idx = np.argmax(similarities)

    if similarities[0, best_match_idx] > 0.3:
        return data[best_match_idx]
    else:
        return None

# Check for Menu Item Prices
def get_item_price(user_input):
    """Returns the price of an item if mentioned in the input."""
    for item, details in menu.items():
        item_lower = item.lower()
        if item_lower in user_input and any(word in user_input for word in ['price', 'cost', 'rate']):
            return f"The price of {item} is {details['price']} and it serves {details['serves']}."
    return None

# Check for Negative Preferences (e.g., "I don't want Latte")
def check_negative_preference(user_input):
    """Checks if the user mentions not wanting a specific item."""
    negation_words = ["don't", "do not", "no", "not", "never", "skip", "avoid"]
    
    for item in menu.keys():
        item_lower = item.lower()
        
        # Check for negative preference pattern
        if any(neg_word in user_input for neg_word in negation_words) and item_lower in user_input:
            return f"Okay, we won't serve {item}. Would you like to try something else?"
    return None

# Bot Interaction Loop
print("CaféBot: Hello! How can I assist you today?")

while True:
    user_input = input("You: ").strip().lower()
    user_input = re.sub(r'[^\w\s]', '', user_input)  # Remove punctuation

    if user_input in ['ok', 'bye', 'exit']:
        print("CaféBot: Goodbye! Have a great day!")
        break

    # Handle negative preferences
    negative_response = check_negative_preference(user_input)
    if negative_response:
        print("CaféBot:", negative_response)
        continue

    # Check for specific item price
    price_response = get_item_price(user_input)
    if price_response:
        print("CaféBot:", price_response)
        continue

    # Show the menu
    elif any(word in user_input for word in ['menu', 'beverage', 'drink', 'drinks']):
        print("CaféBot: Here is our beverage menu:")
        for item in menu.keys():
            print(f"- {item}")
        continue

    # Show prices and servings
    elif any(word in user_input for word in ['price', 'cost', 'serve', 'rates']):
        print("CaféBot: Here are the prices and servings:")
        for item, details in menu.items():
            print(f"- {item}: {details['price']} ({details['serves']})")
        continue

    # Get general response
    general_response = get_best_response(user_input)
    if general_response:
        print("CaféBot:", general_response)
    else:
        # Edge case: if no match is found, show website link
        print("CaféBot: Please visit our website for further details: [www.cafebot.com](#)")
