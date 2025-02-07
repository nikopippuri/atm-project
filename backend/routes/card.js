/**
 *@swagger
 *components:
 *  schemas:
 *    card:
 *      type: object
 *      required:
 *        - card_id
 *        - pin
 *        - tries_left
 *        - locked
 *        - account_id
 *      properties:
 *        card_id:
 *          type: integer
 *          description: The primary key of the card
 *        pin:
 *          type: integer
 *          description: The card's pin number
 *        tries_left:
 *          type: integer
 *          description: How many tries before the card is locked
 *        locked:
 *          type: boolean
 *          description: Is the card locked (true or false)
 *        account_id:
 *          type: integer
 *          description: The foreign key of the card
 */

/**
 * @swagger
 * tags:
 *   - name: card
 *     description: CRUD operations for card table.
 */

/** 
 * @swagger
 * /card:
 *   get:
 *     summary: List of all the cards
 *     tags:
 *       - card
 *     responses:
 *       200:
 *         description: The list of all the cards
 *         content:
 *           application/json:
 *             schema:
 *               type: array
 *               items:
 *                 $ref: '#/components/schemas/card'
 */

/** 
 * @swagger
 * /card:
 *   post:
 *     summary: Creates a new card
 *     tags:
 *       - card
 *     requestBody:
 *       required: true
 *       content:
 *         application/json:
 *           schema:
 *             $ref: '#/components/schemas/card'
 *     responses:
 *       200:
 *         description: Adds a new card
 *         content:
 *           application/json:
 *             schema:
 *               type: array
 *               items:
 *                 $ref: '#/components/schemas/card'
 */

/** 
 * @swagger
 * /card/{card_id}:
 *   put:
 *     summary: Update an existing card
 *     tags:
 *       - card
 *     parameters:
 *       - in: path
 *         name: card_id
 *         required: true
 *         description: The ID of the card to update
 *         schema:
 *           type: integer
 *     requestBody:
 *       required: true
 *       content:
 *         application/json:
 *           schema:
 *             $ref: '#/components/schemas/card'
 *     responses:
 *       200:
 *         description: The updated card
 *         content:
 *           application/json:
 *             schema:
 *               $ref: '#/components/schemas/card'
 *       404:
 *         description: Card not found
 */

/** 
 * @swagger
 * /card/{card_id}:
 *   delete:
 *     summary: Delete an existing card
 *     tags:
 *       - card
 *     parameters:
 *       - in: path
 *         name: card_id
 *         required: true
 *         description: The ID of the card to delete
 *         schema:
 *           type: integer
 *     responses:
 *       200:
 *         description: Card deleted successfully
 *       404:
 *         description: Card not found
 */


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