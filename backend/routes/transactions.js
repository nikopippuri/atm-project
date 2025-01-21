const express = require('express');
const router = express.Router();
const transactions = require('../models/transactions_model');


router.get('/', function(req,res){
    transactions.getAll(function(err,result){
        if(err) {
            res.json(err)
        }
    
        else { 
        res.json(result);
    }
})
});

router.get('/:id',
    function (request, response) {
        transactions.getById(request.params.id, function (err, result) {
            if (err) {
                response.json(err);
            } else {
                response.json(result);
            }
        })
    });

    router.post('/', 
        function(request, response) {
          transactions.add(request.body, function(err, result) {
            if (err) {
              response.json(err.errno);
              console.log(err)
            } else {
              response.json(result.affectedRows);
            }
          });
        });    

        router.put('/:id', function(request, response) {
            transactions.update(request.params.id, request.body, function(err, result) {
              if (err) {
                response.json(err.errno);
                console.log(err)
              } else {
                response.json(result.changedRows);
              }
            });
          });    

        router.delete('/:id', function(request,response){
          transactions.delete(request.params.id,function(err, result) {
            if (err) {
              response.json(err.errno);
              console.log(err)
            } else {
              response.json(result);
            }
          });
        });    


module.exports=router;