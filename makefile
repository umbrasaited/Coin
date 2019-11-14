make:
	g++ -std=c++14 transaction.cpp user.cpp Block.cpp BlockChain.cpp 2_blockchain.cpp -o main
	./main
	rm main