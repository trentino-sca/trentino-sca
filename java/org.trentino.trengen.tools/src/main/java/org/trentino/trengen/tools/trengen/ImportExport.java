package org.trentino.trengen.tools.trengen;

import java.io.File;
import java.net.MalformedURLException;
import java.util.List;

import javax.xml.bind.JAXBElement;

import org.apache.log4j.Logger;
import org.trentino.trengen.sca.model.CPPExport;
import org.trentino.trengen.sca.model.CPPImport;
import org.trentino.trengen.sca.model.ContributionType;
import org.trentino.trengen.sca.model.Export;
import org.trentino.trengen.sca.model.Import;
import org.trentino.trengen.tools.scavalidation.DirectoryScanner;
import org.trentino.trengen.tools.scavalidation.XmlParser;
import org.trentino.trengen.xml.schema.QName;

/**
 * used to read imported names from other contributions
 * @author z002ttbb
 *
 */
public class ImportExport {

	protected static Logger log = Logger.getLogger(ImportExport.class);
	public static void scanImportedContributions(String contributions) {
		if(contributions==null)
		{
			log.info("No imported contributions to scan");
			return;
		}
		
		String[] parts = contributions.split("[;,]");
		for(String contribution : parts){
			File f = new File(contribution,"META-INF/sca-contribution.xml");
			f = f.getAbsoluteFile();
			log.info("Parsing external contribution from file "+f.getPath());
			if(!f.exists()){
				log.warn("declared import is not a contribution (sca-contribution.xml not found). Will not be processed: "+contribution);
				continue;
			}
			
			ContributionType contributionType;
			try {
				 contributionType = (ContributionType) XmlParser.parseArtifact(f.toURI().toURL());
			} catch (Exception e) {
				log.warn("Cannot parse imported file "+f.getAbsolutePath()+"\n Skipping file because of "+e.getMessage());
				continue;
			}
			if(contributionType==null){
				throw new IllegalStateException("ContributionType cannot be null");
			}
			
			if(contributionType.getVersion()==null){
				contributionType.setVersion("0.0.0");
			}
			
			List<JAXBElement<? extends Export>>  exports = contributionType.getExportBase();
			for(JAXBElement<? extends Export> export: exports){
				Export exp = export.getValue();
				if(exp==null || !(exp instanceof CPPExport)){
					continue;
				}
				CPPExport cpp = (CPPExport) exp;
				if(cpp.getVersion()==null){
					cpp.setVersion(contributionType.getVersion());
				}
				DirectoryScanner.addExportedName(cpp,f);
			}
		}
	}
	
	
	public static void scanImportedDirectories(ContributionType contributionType) {
		if(contributionType.getVersion()==null){
			contributionType.setVersion("0.0.0");
		}
		List<JAXBElement<? extends Import>>  imports = contributionType.getImportBase();
		for(JAXBElement<? extends Import> impEl: imports){
			Import imp = impEl.getValue();
			if(imp==null || !(imp instanceof CPPImport)){
				continue;
			}
			CPPImport cpp = (CPPImport) imp;
			if(cpp.getVersion()==null){
				cpp.setVersion(contributionType.getVersion());
			}
			DirectoryScanner.addImportedName(cpp);
		}
		
	}


	public static void convertImportsExportsToMirrorModel(ContributionType contribution, 
			org.trentino.trengen.scamodelmirror.ContributionType mirrorContribution) {
		for(JAXBElement<? extends Export> entry : contribution.getExportBase()){
			if(!entry.isNil() && !(entry.getValue() instanceof CPPExport)){
				continue;
			}
			CPPExport exportOrig = (CPPExport) entry.getValue();
			org.trentino.trengen.scamodelmirror.CPPExport export = new org.trentino.trengen.scamodelmirror.CPPExport();
			export.setName(QName.fromQName(exportOrig.getName()));
			export.setPath(exportOrig.getPath());
			export.setVersion(exportOrig.getVersion());
			export.setNameGen("export");
		}
		
		for(JAXBElement<? extends Import> entry : contribution.getImportBase()){
			if(!entry.isNil() && !(entry.getValue() instanceof CPPImport)){
				continue;
			}
			CPPImport impOrig = (CPPImport) entry.getValue();
			org.trentino.trengen.scamodelmirror.CPPImport imp = new org.trentino.trengen.scamodelmirror.CPPImport();
			imp.setName(QName.fromQName(impOrig.getName()));
			imp.setLocation(impOrig.getLocation());
			imp.setVersion(impOrig.getVersion());
			imp.setNameGen("importVal");
		}
	}

}
