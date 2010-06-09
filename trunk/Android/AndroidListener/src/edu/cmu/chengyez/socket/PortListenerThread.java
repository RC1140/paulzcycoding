package edu.cmu.chengyez.socket;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import javax.net.ServerSocketFactory;

import android.util.Log;

public class PortListenerThread implements Runnable {

	public static final int DEFAULTPORT = 4444;
	public static final String TAG = PortListenerThread.class.getName();

	/**
	 * @param args
	 */
	public static void start() {
		new Thread(new PortListenerThread()).start();
	}

	public void run() {
		ServerSocket serverSocket = null;
		try {
			serverSocket = ServerSocketFactory.getDefault().createServerSocket(
					DEFAULTPORT);
		} catch (IOException e) {
			Log.e(TAG, e.getMessage());
			return;
		}

		while (true) {
			Socket clientSocket = null;
			try {
				clientSocket = serverSocket.accept();
			} catch (IOException e) {
				Log.e(TAG, e.getMessage());
				continue;
			}
			Log.d(TAG, "Connection Established");
			new Thread(new ConnectionThread(clientSocket)).start();
		}
	}
}
