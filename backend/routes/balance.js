const express = require('express');
const router = express.Router();
const accountModel = require('../models/balance_model'); 

router.get('/balance', (req, res) => {
    console.log("Received request for:", req.originalUrl);
    console.log("GET /balance query:", req.query);

    const { account_id } = req.query; 

    if (!account_id) {
        return res.status(400).json({ error: "Account ID is required" });
    }

    accountModel.getBalance(account_id, (err, result) => {
        if (err) {
            console.error("Error fetching balance:", err.message);
            return res.status(500).json({ error: err.message });
        }

        if (!result) {
            return res.status(404).json({ error: "Account not found" });
        }

        console.log("Balance retrieved:", result);
        res.status(200).json({ balance: result.balance });
    });
});

module.exports = router;
