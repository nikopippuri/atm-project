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
 *     summary: Creates a new card (Need to create hashed pin with hash.js)
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
 * /login:
 *   post:
 *     summary: Login with card_id and pin to generate token for authorization
 *     tags:
 *       - Authorize
 *     requestBody:
 *       required: true
 *       content:
 *         application/json:
 *           schema:
 *             type: object
 *             properties:
 *               card_id:
 *                 type: integer
 *                 description: The card_id for authentication
 *               pin:
 *                 type: string
 *                 description: The pin for authentication
 *     responses:
 *       200:
 *         description: Successfully logged in and returned JWT token
 *         content:
 *           application/json:
 *             schema:
 *               type: object
 *               properties:
 *                 token:
 *                   type: string
 *                   description: The JWT token
 *       401:
 *         description: Unauthorized - Invalid card_id or pin
 *       400:
 *         description: Bad request - Missing card_id or pin
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