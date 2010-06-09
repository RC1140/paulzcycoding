package edu.cmu.chengyez.socket;

import java.io.IOException;
import java.net.Socket;

import android.util.Log;

public class ConnectionThread implements Runnable {
	private Socket clientSocket = null;
	private static ProcessBuilder processBuilder = null;
	private Process process;
	private static final String TAG = ConnectionThread.class.getName();

	public ConnectionThread(Socket clientSocket) {
		this.clientSocket = clientSocket;
	}

	@Override
	public void run() {
		processBuilder = getProcessBuilder();
		try {
			process = processBuilder.start();
		} catch (IOException e) {
			Log.e(TAG, e.getMessage());
			return;
		}

		SyncThread sync1 = null;
		SyncThread sync2 = null;
		try {
			sync1 = new SyncThread(process.getOutputStream(), clientSocket
					.getInputStream());
			sync2 = new SyncThread(clientSocket.getOutputStream(), process
					.getInputStream());
		} catch (IOException e) {
			Log.e(TAG, e.getMessage());
			return;
		}
		Log.e(TAG, "Starting Syncronizer...");

		sync1.setName("Sync1");
		sync2.setName("Sync2");
		sync1.start();
		sync2.start();

		while (true) {
			if (sync1.isStopped()) {
				sync2.sendStopSignal();
				break;
			}
			if (sync2.isStopped()) {
				sync1.sendStopSignal();
				break;
			}
		}

		try {
			if (!clientSocket.isClosed()) {
				clientSocket.close();
			}
		} catch (IOException e) {
			Log.e(TAG, e.getMessage());
		}
		
		try {
			process.exitValue();
		} catch (IllegalThreadStateException e) {
			process.destroy();
		}
		Log.d(TAG, "Connection Closed");
	}

	private ProcessBuilder getProcessBuilder() {
		if (processBuilder == null) {
			processBuilder = new ProcessBuilder("/system/bin/sh", "-");
			processBuilder.redirectErrorStream(true);
		}
		return processBuilder;
	}

}
