/*************************************************************************
 * Copyright (c) 2014 eProsima. All rights reserved.
 *
 * This copy of eProsima RTPS is licensed to you under the terms described in the
 * EPROSIMARTPS_LIBRARY_LICENSE file included in this distribution.
 *
 *************************************************************************/

/**
 * @file StatefulWriter.h
 *
 *  Created on: Mar 17, 2014
 *      Author: Gonzalo Rodriguez Canosa
 *      email:  gonzalorodriguez@eprosima.com
 *              grcanosa@gmail.com  	
 */

#ifndef STATEFULWRITER_H_
#define STATEFULWRITER_H_


#include "eprosimartps/writer/RTPSWriter.h"

#include "eprosimartps/writer/ReaderProxy.h"


namespace eprosima {
namespace rtps {

/**
 * Class StatefulWriter, specialization of RTPSWriter that maintains information of each matched Reader.
 * @ingroup WRITERMODULE
 */
class StatefulWriter: public RTPSWriter {
public:
	//StatefulWriter();
	virtual ~StatefulWriter();

	StatefulWriter(const PublisherAttributes& param,
			const GuidPrefix_t&guidP, const EntityId_t& entId);

	/**
	 * Add a matched reader to the writer.
	 * @param Rp Structure containing the parameters for the reader.
	 * @return True if correct.
	 */
	bool matched_reader_add(ReaderProxy_t& Rp);
	/**
	 * Remove a reader from the writer list.
	 * @param Rp Structure containing the parameters.
	 * @return True if correct
	 */
	bool matched_reader_remove(ReaderProxy_t& Rp);
	/**
	 * Remove a reder based on its guid.
	 * @param readerGuid GUID_t of the reader.
	 * @return True if correct.
	 */
	bool matched_reader_remove(GUID_t& readerGuid);

	/**
	 * Find a Reader Proxy in this writer.
	 * @param[in] readerGuid The GUID_t of the reader.
	 * @param[out] RP Pointer to pointer to return the ReaderProxy.
	 * @return True if correct.
	 */
	bool matched_reader_lookup(GUID_t& readerGuid,ReaderProxy** RP);

	/**
	 * Find out if a change is acked by all ReaderProxy.
	 * @param change Pointer to the change.
	 * @return True if correct.
	 */
	bool is_acked_by_all(CacheChange_t* change);

	/**
	 * Add the provided change to the unsent changes vectors of all matched Readers.
	 * @param[in] change Pointer to the change
	 */
	void unsent_change_add(CacheChange_t* change);

	/**
	 * Method to indicate that there are changes not sent in some of all ReaderProxy.
	 */
	void unsent_changes_not_empty();




	bool removeMinSeqCacheChange();
	bool removeAllCacheChange(int32_t* n_removed);

	void incrementHBCount(){++m_heartbeatCount;}

private:
	//! Vector containin all the associated ReaderProxies.
		std::vector<ReaderProxy*> matched_readers;

		PublisherTimes m_PubTimes;

		Count_t m_heartbeatCount;


};

} /* namespace rtps */
} /* namespace eprosima */

#endif /* STATEFULWRITER_H_ */
