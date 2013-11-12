package org.trentino.trengen.tools.protobuf;

import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.util.ArrayList;
import java.util.List;

import org.apache.log4j.Logger;
import org.trentino.trengen.tools.scavalidation.DirectoryScanner;
import org.trentino.trengen.tools.trengen.Trengen;

public class CppFileGenerationWithProtoc {
	protected static final Logger	logger	= Logger.getLogger(CppFileGenerationWithProtoc.class);



	/**
	 * protoc.exe is assumed to be in user.dir
	 */
	public boolean generateProtocFiles() {
		// scan all the proto files under Generation folder.
		File outputDir = new File(Trengen.getOutDir());
        List<File> sp = new ArrayList<File>();
        sp.add(new File(Trengen.getOutDir()));
		List<File> protoFiles = DirectoryScanner.SearchArtifacts(sp, "proto");
		if(protoFiles.size() == 0)
		{
			logger.error("No .proto is found in " + sp);
			return false;
		}
		String exePath = CppFileGenerationWithProtoc.class.getProtectionDomain().getCodeSource().getLocation().getPath();

		if(exePath.contains("target/classes") || exePath.contains("target\\classes")) // while running from
		                                                                              // Eclipse
		{
			exePath = exePath.replace("target/classes/", "");
			exePath = exePath.replace("target\\classes\\", "");
		}
		else if(exePath.contains("Trengen.jar")) // while running with
		                                         // Trengen.exe
		{
			exePath = exePath.replace("Trengen.jar", "");
		}

		for (File protoFile : protoFiles)
		{
			// String protofiles = "*.proto";
			ProcessBuilder pb = null;
			try
			{

				pb = new ProcessBuilder(exePath + "protoc", "--cpp_out=" + Trengen.getOutDir(), protoFile.getName());
				pb.redirectErrorStream(true);
				pb.directory(outputDir);
				Process p = pb.start();
				OutputStream stdin = null;
				InputStream stdout = null;
				InputStream stderr = null;
				try
				{
					stdin = p.getOutputStream();
					stdout = p.getInputStream();
					stderr = p.getErrorStream();
					String line;
					StringBuffer buffer = new StringBuffer();
					BufferedReader bufferedStderr = new BufferedReader(new InputStreamReader(stderr));
					while ((line = bufferedStderr.readLine()) != null)
					{
						buffer.append(line).append("\n");
					}
					bufferedStderr.close();

					BufferedReader bufferedStdout = new BufferedReader(new InputStreamReader(stdout));
				
					while ((line = bufferedStdout.readLine()) != null)
					{
						buffer.append(line).append("\n");
					}
	                
					logger.info(buffer.toString());
					p.waitFor();

					int val = p.exitValue();
					if(val != 0)
					{
						logger.error(buffer.toString());
						return false;
					}
				} catch (InterruptedException e)
				{
					logger.error("Trengen could not run the protoc compiler!...");
					return false;
				} finally
				{
					if(stdin != null)
						stdin.close();
					if(stderr != null)
						stderr.close();
					if(stdout != null)
						stdout.close();
				}
			} catch (IOException e)
			{
				logger.error("Trengen could not run the protoc compiler!...");
				return false;
			}
		}
		return true;
	}
}
