import serial
import os
import sys
import signal


def handler(signum, frame):
    sys.exit()


def main():
    # 割り込みで終了するためにハンドラを設定
    signal.signal(signal.SIGINT, handler)

    # シリアルポートを開く
    ser = serial.Serial(
        "COM5", baudrate=115200, timeout=None, parity=serial.PARITY_NONE
    )

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

    # Ctrl-C が押されるまで記録し続ける
    while True:
        # bit落ちによるエンコードミスを無視
        try:
            outputFile.write(ser.readline().decode("utf-8"))
        except UnicodeDecodeError:
            continue


if __name__ == "__main__":
    main()
