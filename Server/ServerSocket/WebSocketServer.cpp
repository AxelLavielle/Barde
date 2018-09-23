class WebSocketServer {
    public:
        void handshake();
        bool isWebSocketData();
        void sendMsg(char *msg);
        char *receiveMsg();

    private:
        void pingPongMsg();
};