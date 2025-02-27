const OLLAMA_URL = "http://localhost:11434/api/generate";

class ChatModel {
    static async getResponse(message) {
        const fetch = (await import("node-fetch")).default; // Käytä dynaamista importtia

        try {

            // Lähettää ollamalle viestin
            
            const response = await fetch(OLLAMA_URL, {
                method: "POST",
                headers: { "Content-Type": "application/json" },
                body: JSON.stringify({
                    model: "mybankbot",
                    prompt: message,
                    stream: false,
                }),
            });

            // Saa vastauksen ja palauttaa sen jsonina

            const data = await response.json();
            return data.response;
        } catch (error) {
            console.error("Ollama API virhe:", error);
            return "Virhe chatbotin kanssa.";
        }
    }
}

module.exports = ChatModel;
