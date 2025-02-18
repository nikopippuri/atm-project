const express = require('express');
const router = express.Router();
const accountModel = require('../models/account_model'); 

router.post('/withdraw', (req, res) => {
    console.log("POST /withdraw body:", req.body);

    const { account_id, amount } = req.body;

    accountModel.withdraw(account_id, amount, (err, result) => {
        if (err) {
            console.error("Error during withdrawal:", err.message);
            return res.status(500).json({ message: err.message });
        }

        console.log("Withdrawal response:", result);
        res.status(200).json(result);  
    });
});

module.exports = router;

