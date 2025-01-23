const express = require('express');
const router = express.Router();
const accountModel = require('../models/account_model'); 

router.post('/withdraw', (req, res) => {
    console.log("POST /withdraw body:", req.body); 

    const { account_id, amount } = req.body;

    accountModel.withdraw(account_id, amount, (err, result) => {
        if (err) {
            console.error("Error during withdrawal:", err.message);
            return res.status(500).json({ error: err.message });
        }
        
        console.log("Withdrawal successful, result:", result);
        res.status(200).json(result);
    });
});

module.exports = router;

