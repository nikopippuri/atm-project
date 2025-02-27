const express = require("express");
const ChatModel = require("../models/chatbot_model");

const router = express.Router();

// Vastaanottaa post viestin qt:lta requna, jossa messagena viesti

router.post("/", async (req, res) => {
    const userMessage = req.body.message;

    if (!userMessage) {
        return res.status(400).json({ response: "Virheellinen viesti." });
    }

// Välittää viestin ollaamalle

    const botResponse = await ChatModel.getResponse(userMessage);
    res.json({ response: botResponse });
});

module.exports = router;