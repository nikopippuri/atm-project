const express = require('express');
const router = express.Router();
const card = require('../models/card_model');

router.get('/',function(request,response){
card.getAll(function(err,result){
    if(err){
        response.json(err);
    }
    else {
        response.json(result);
    }
})
});

router.get('/:id',function(request,response){
    card.getById(request.params.id,function(err,result){
        if(err){
            response.json(err);
        }
        else {
            response.json(result);
        }
    })
    });

    router.post('/',function(request,response){
        card.add(request.body,function(err,result){
            if(err){
                response.json(err);
            }
            else {
                response.json(result);
            }
        })

    });

    router.put('/:upd',function(request,response){
        card.update(request.params.upd,request.body,function(err,result){
            if(err){
                response.json(err);
            }
            else {
                response.json(result);
            }
        })

    });
    
    router.delete('/:del',function(request,response){
        card.delete(request.params.del,function(err,result){
            if(err){
                response.json(err);
            }
            else {
                response.json(result);
            }
        })
    });

   
module.exports=router;