package edu.cmu.chengyez.socket;

import java.io.FileDescriptor;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.net.Socket;

import android.util.Log;

import com.google.ase.Exec;

public class ConnectionThread implements Runnable {
	private Socket clientSocket = null;
	private static final String TAG = ConnectionThread.class.getName();
	private FileInputStream is;
	private FileOutputStream os;
	private FileDescriptor shellFd;

	public ConnectionThread(Socket clientSocket) {
		this.clientSocket = clientSocket;
	}

	@Override
	public void run() {
		int[] pids=new int[1];
		try {
			shellFd = Exec.createSubprocess("/system/bin/sh", "-", null, pids);
		} catch (Exception e) {
			Log.e(TAG, "Cannot start local shell", e);
			return;
		}
		
		is = new FileInputStream(shellFd);
		os = new FileOutputStream(shellFd);

		SyncThread sync1 = null;
		SyncThread sync2 = null;
		try {
			sync1 = new SyncThread(os, clientSocket.getInputStream());
			sync2 = new SyncThread(clientSocket.getOutputStream(), is);
		} catch (IOException e) {
			Log.e(TAG, e.getMessage());
			return;
		}
		Log.e(TAG, "Starting Syncronizer...");

		sync1.setName("Sync1");
		sync2.setName("Sync2");
		sync1.start();
		sync2.start();
		
		Exec.waitFor(pids[0]);
		sync1.sendStopSignal();
		sync2.sendStopSignal();

		try {
			if (!clientSocket.isClosed()) {
				clientSocket.close();
			}
		} catch (IOException e) {
			Log.e(TAG, e.getMessage());
		}

		Log.d(TAG, "Connection Closed");
	}
}
