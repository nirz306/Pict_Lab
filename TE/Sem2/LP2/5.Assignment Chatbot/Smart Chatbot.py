import streamlit as st
from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.metrics.pairwise import cosine_similarity
import numpy as np

# Sample phrases for each intent
intent_examples = {
    "greeting": ["hello", "hi", "hey", "good morning"],
    "menu": ["what's on the menu", "show me the drinks", "what do you serve"],
    "order": ["i want to order", "can i get a coffee", "i'd like to have a tea", "get me a cake", "i want cake"],
    "hours": ["when do you open", "what are your hours", "closing time"],
    "goodbye": ["bye", "goodbye", "see you later"],
    "thanks": ["thank you", "thanks a lot", "thanks"],
    "reservation": ["book a table", "i need a reservation", "reserve for two"],
    "location": ["where are you located", "what's your address", "location of the cafe"],
    "wifi": ["do you have wifi", "internet available", "wifi password"],
    "delivery": ["do you deliver", "home delivery", "can i order from home"],
    "negative": ["i don't want cake", "no coffee", "not interested in tea", "i do not want anything sweet"]
}

# Responses
intent_responses = {
    "greeting": "Welcome to Brew Café! What can I get for you today?",
    "menu": "Here's our menu:\n Coffee\nTea\n Croissant\n Cake",
    "order": "Sure! What would you like to order?",
    "hours": "We're open from 8 AM to 8 PM every day!",
    "goodbye": "Thanks for visiting Brew Café. Have a great day!",
    "thanks": "You're welcome! ",
    "reservation": "Sure! We can reserve a table for you. For how many people?",
    "location": "We're located at 123 Coffee Street, Brewtown ",
    "wifi": "Yes! Free Wi-Fi is available. The password is brewcoffee123.",
    "delivery": "Yes, we offer home delivery within 5 km. 🍽",
    "negative": "No problem! How about trying something else from our menu?"
}

# Updated detailed items with prices and no follow-up questions
detailed_items = {
    "cake": " We have:\n- Chocolate Cake : ₹150\n- Red Velvet ❤: ₹180\n- Cheesecake : ₹200\n(Available in egg & eggless options)",
    "coffee": " Coffee options:\n- Espresso: ₹100\n- Cappuccino: ₹120\n- Latte: ₹130",
    "tea": "Tea options:\n- Green Tea: ₹80\n- Masala Chai: ₹70\n- Lemon Tea: ₹75",
    "croissant": "Croissants:\n- Butter: ₹90\n- Almond: ₹110\n- Chocolate: ₹120"
}


# Combine examples
all_examples = []
intent_tags = []
for intent, examples in intent_examples.items():
    all_examples.extend(examples)
    intent_tags.extend([intent] * len(examples))

# Vectorize
vectorizer = TfidfVectorizer()
example_vectors = vectorizer.fit_transform(all_examples)

# UI Setup
st.title("Brew Café Chatbot")

if "chat_history" not in st.session_state:
    st.session_state.chat_history = []

user_input = st.text_input("Ask something:")

if user_input:
    if user_input.lower() == "exit":
        st.session_state.chat_history.append(("User", user_input))
        st.session_state.chat_history.append(("Bot", "Goodbye! Chat ended."))
    else:
        input_vector = vectorizer.transform([user_input])
        similarity = cosine_similarity(input_vector, example_vectors)
        best_match_index = np.argmax(similarity)
        best_match_intent = intent_tags[best_match_index]
        best_score = similarity[0][best_match_index]

        if best_score < 0.3:
            response = "I'm sorry, I didn't understand that. Could you rephrase?"
        else:
            # Step 1: Handle base response
            response = intent_responses[best_match_intent]

            # Step 2: Add detailed food item options
            if best_match_intent == "order":
                for item in detailed_items:
                    if item in user_input.lower() and "don't" not in user_input.lower() and "do not" not in user_input.lower():
                        response += f"\n\n {detailed_items[item]}"
                        break

        st.session_state.chat_history.append(("User", user_input))
        st.session_state.chat_history.append(("Bot", f"{response} (Confidence: {best_score:.2f})"))

# Display chat
for speaker, message in st.session_state.chat_history:
    if speaker == "User":
        st.markdown(f" **You:** {message}")
    else:
       st.markdown(f" **{speaker}:** {message}")
