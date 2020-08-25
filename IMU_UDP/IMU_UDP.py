# This python script listens on UDP port 3333
# for messages from the ESP32 board and prints them
import socket
import sys
import os
import signal


# 割り込みハンドラ
def handler(signum, frame):
    sys.exit()


def main():
    # 割り込みで終了するためにハンドラを設定
    signal.signal(signal.SIGINT, handler)

    # ソケットを作成
    try:
        s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    except socket.error as msg:
        print(
            "Failed to create socket. Error Code : "
            + str(msg[0])
            + " Message "
            + msg[1]
        )
        sys.exit()

    # ポート接続
    try:
        s.bind(("", 3333))
    except socket.error as msg:
        print("Bind failed. Error: " + str(msg[0]) + ": " + msg[1])
        sys.exit()

    # ファイル出力先ディレクトリを設定
    outputDirPath = "./outputs"

    # ファイル名の設定を要求
    print("file name?: ", end="")
    outputFileName = input()
    outputFilePath = os.path.join(outputDirPath, outputFileName + ".csv")

    # 出力先ファイルを開く
    outputFile = open(outputFilePath, mode="w")

    print("logging started. (Ctrl-C to stop.)")

    # 最初にヘッダを書き込み
    outputFile.write("Time, AccX, AccY, AccZ, GyrX, GyrY, GyrZ, Pitch, Roll, Yaw\n")

    while True:
        d = s.recvfrom(1024)  # バッファサイズ1024は適宜変更
        data = d[0]

        if not data:
            break

        try:
            outputFile.write(data.decode("utf-8"))
        except UnicodeDecodeError:  # bit落ちによるエンコードミスを無視
            continue

    s.close()


if __name__ == "__main__":
    main()
