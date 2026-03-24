#include "bulletin.h"
#include <assert.h>
#include <stdio.h> // temporary, only for FILE pointer for debugging purposes

//static FILE* s_fp = 0;

HP_BulletinBoard::HP_BulletinBoard()
{
//	s_fp = fopen("bulletin.out", "w");
//	assert(s_fp);
	CreateBB();
	PK_BB_set_status(m_BB, PK_BB_status_on_c);
}


HP_BulletinBoard::~HP_BulletinBoard()
{
//	fclose(s_fp);
}


bool HP_BulletinBoard::FilterEvent(PK_ENTITY_t bbEntity,
						PK_BB_event_t bbEvent_type,
						unsigned long num_entities,
						PK_ENTITY_t *created, unsigned long *num_created,
						PK_ENTITY_t *deleted, unsigned long *num_deleted,
						PK_ENTITY_t *altered, unsigned long *num_altered,
						PK_ENTITY_t *transformed, unsigned long *num_transformed) // specifies allocated size of notable_entities and notable_event_types arrays
{
	PK_ERROR_t error;
	PK_CLASS_t bbEntityClass=0;
	unsigned long i;
	bool ignore_this_event = false;
	PK_LOGICAL_t is_entity;

	(void)num_transformed;
	(void)transformed;
	(void)num_entities;
	assert(bbEntity != 0);

	error = PK_ENTITY_is(bbEntity, &is_entity);
	assert(!error);
	if (is_entity) // this entity has not been deleted
	{
		error = PK_ENTITY_ask_class(bbEntity, &bbEntityClass);
		assert(!error);
	}
	else
	{
		if (bbEvent_type != PK_BB_event_delete_c)
			return true; // do nothing if this entity has been deleted.
			// process a delete event once, when we see the real thing.

	}

	switch(bbEvent_type)
	{
	case PK_BB_event_create_c:
		switch(bbEntityClass)
		{
		case PK_CLASS_edge:
		case PK_CLASS_face:
			created[*num_created] = bbEntity;
			(*num_created)++;
			//fprintf(s_fp, "\nAdding entity %d of class %d to created array\n\n", bbEntity, bbEntityClass);
			break;
		default:
			// do nothing; no need to consider body creation events.
			break;
		}
/*
		if(bbEntityClass == PK_CLASS_body)
		{
// ** change ** no need to consider body creation events.
//			created[*num_created] = bbEntity;
//			(*num_created)++;
//				fprintf(s_fp, "\nAdding entity %d  (BODY)  to created array\n\n", bbEntity, bbEntityClass);
			// *FIX maybe we need to check for previously handled
			// edge and face creation events, though I think these come
			// later in the queue than the body creation events.
			return true;
		}

		else
		{
			PK_CLASS_t entityClass;
			if (*num_created > 0)
			{
				i = (*num_created); // start at the end (most recent) of the created
				// array and work towards the beginning.
				do
				{
					i--;
					if (created[i] != 0) // don't consider "nullified" entries
					{
						PK_LOGICAL_t is_entity;
						error = PK_ENTITY_is(created[i], &is_entity);
						assert(!error);
						if (!is_entity) // entity created[i] has been deleted
						{
							created[i] = 0;
							continue;
						}
						error = PK_ENTITY_ask_class(created[i], &entityClass);
						assert(!error);
						if (entityClass == PK_CLASS_body)
						{
							PK_BODY_t bbEntity_owning_body;
							switch (bbEntityClass)
							{
							case PK_CLASS_body:
								assert(0); // code is broken, this shouldn't happen
								break;

							case PK_CLASS_edge:
								error = PK_EDGE_ask_body(bbEntity, &bbEntity_owning_body);
								assert(!error);
								if (bbEntity_owning_body == created[i])
									// this edge creation event is superceded by 
									// a previously registered body creation event.
									ignore_this_event = true;
								break;

							case PK_CLASS_face:
								error = PK_FACE_ask_body(bbEntity, &bbEntity_owning_body);
								assert(!error);
								if (bbEntity_owning_body == created[i])
									// this face creation event is superceded by 
									// a previously registered body creation event.
									ignore_this_event = true;
								break;
							
							default:
								break;
							}
						}
					}
					if (ignore_this_event)
						break; // short-cut this do-while loop
					assert(i < (*num_created));
				}
				while (i != 0);
			}
*/
//			if (!ignore_this_event)
//			{
//				created[*num_created] = bbEntity;
//				(*num_created)++;
//				fprintf(s_fp, "\nAdding entity %d of class %d to created array\n\n", bbEntity, bbEntityClass);
//
//			}
//		}
		return true;
		break;
    case PK_BB_event_delete_c:
//		assert(0);
		// this is a tough case.  until/unless someone comes up with a better idea,
		// we'll do a brute-force approach here and put everything deleted into the deleted array.
		deleted[*num_deleted] = bbEntity;

		// should purge other lists of mentions of this entity?

		// I don't think this is necessary, as we will have ignored
		// all of these type of evens by bailing out early above,
		// see 	error = PK_ENTITY_is(bbEntity, &is_entity); call above.
		// if an entity has been deleted, is_entity will be false.

		// skipping this step saves some time, don't do it. 
		
//		for (i = 0; i < *num_created; i++)
//			if (created[i] == bbEntity)
//				created[i] = 0;
//		for (i = 0; i < *num_altered; i++)
//			if (altered[i] == bbEntity)
//				altered[i] = 0;
//		for (i = 0; i < *num_transformed; i++)
//			if (transformed[i] == bbEntity)
//				transformed[i] = 0;

		//fprintf(s_fp, "Adding entity %d to deleted array\n", bbEntity);
		(*num_deleted)++;
		break;
    case PK_BB_event_copy_c:
		break;
	case PK_BB_event_merge_c:
		assert(0);
		break;
//    case PK_BB_event_transfer_c:
//		assert(0);
//		break;
    case PK_BB_event_split_c:
		assert(0);
		break;
    case PK_BB_event_transform_c:
		break;
    case PK_BB_event_change_attrib_c:
//		assert(0);
		break;
    case PK_BB_event_change_c:
    case PK_BB_event_transfer_c:

		if (is_entity) // this entity has not been deleted
		{
			error = PK_ENTITY_ask_class(bbEntity, &bbEntityClass);
			assert(!error);
			if ((bbEntityClass == PK_CLASS_edge) || (bbEntityClass == PK_CLASS_face))
			{
				// look to see if we already have a create or change event for this entity
				PK_CLASS_t entityClass;

				// first look for creation events
				if (*num_created > 0)
				{
					i = (*num_created); // start at the end (most recent) of the created
					// array and work towards the beginning.
					do
					{
						i--;
						if (created[i] != 0) // don't consider "nullified" entries
						{
							PK_LOGICAL_t is_entity;
							error = PK_ENTITY_is(created[i], &is_entity);
							assert(!error);
							if (!is_entity) // entity created[i] has been deleted
							{
								created[i] = 0;
								continue;
							}
							error = PK_ENTITY_ask_class(created[i], &entityClass);
							assert(!error);
							if (entityClass == PK_CLASS_body)
							{
								PK_BODY_t bbEntity_owning_body;
								switch (bbEntityClass)
								{
								case PK_CLASS_body:
									assert(0); // code is broken, this shouldn't happen
									break;

								case PK_CLASS_edge:
									error = PK_EDGE_ask_body(bbEntity, &bbEntity_owning_body);
									assert(!error);
									if (bbEntity_owning_body == created[i])
										// this edge creation event is superceded by 
										// a previously registered body creation event.
										ignore_this_event = true;
									break;
								case PK_CLASS_face:
									error = PK_FACE_ask_body(bbEntity, &bbEntity_owning_body);
									assert(!error);
									if (bbEntity_owning_body == created[i])
										// this face creation event is superceded by 
										// a previously registered body creation event.
										ignore_this_event = true;
									break;
								
								default:
									break;
								}
							}
							else if (bbEntity == created[i])// already had a create event, ignore the change
							{
								ignore_this_event = true;
							}
						}
						if (ignore_this_event)
							break; // short-cut this do-while loop
						assert(i < (*num_created));
					}
					while (i != 0);
				} // num_created > 0



				// now look for changed events
								// first look for creation events
				if ((!ignore_this_event) && (*num_altered > 0))
				{
					i = (*num_altered); // start at the end (most recent) of the created
					// array and work towards the beginning.
					do
					{
						i--;
						if (bbEntity == altered[i])// already had an alter event, ignore the change
						{
							ignore_this_event = true;
							break;
						}
						assert(i < (*num_altered));
					}
					while (i != 0);
				} // num_altered > 0
				if (!ignore_this_event)
				{
					altered[*num_altered] = bbEntity;
					(*num_altered)++;
					//fprintf(s_fp, "Adding entity %d of class %d to altered array\n\n", bbEntity, bbEntityClass);
				}


			}
		}
		break;
	default:
//		assert(0);
		break;


	}
	return true;
}



bool HP_BulletinBoard::GetChangedEntities(PK_ENTITY_t **created, unsigned long *num_created,
						PK_ENTITY_t **deleted, unsigned long *num_deleted,
						PK_ENTITY_t **altered, unsigned long *num_altered,
						PK_ENTITY_t **transformed, unsigned long *num_transformed)
{
	PK_ERROR_t error;
	unsigned long i;
	int n_entities;
	unsigned long num_entities;
	int* events;
	PK_ENTITY_t* bbentities;
	unsigned long num_notable_events;
	PK_BB_event_t* event_types;
	PK_CLASS_t* classes;
	int* user_fields;

	PK_ENTITY_t* temp_created = 0;
	PK_ENTITY_t* temp_deleted = 0;
	PK_ENTITY_t* temp_altered = 0;
	PK_ENTITY_t* temp_transformed = 0;
	unsigned long temp_num_created = 0;
	unsigned long temp_num_deleted = 0;
	unsigned long temp_num_altered = 0;
	unsigned long temp_num_transformed = 0;
	unsigned long temp_num = 0;

	// initialize variables to be returned

	assert(num_created);
	assert(num_deleted);
	assert(num_altered);
	assert(num_transformed);

	assert(created);
	assert(deleted);
	assert(altered);
	assert(transformed);

	*num_created = 0;
	*num_deleted = 0;
	*num_altered = 0;
	*num_transformed = 0;
	
	*created = 0;
	*deleted = 0;
	*altered = 0;
	*transformed = 0;
	

	error = PK_BB_output_events(m_BB, 
		                PK_LOGICAL_true, 
						&n_entities, 
						&events,
						&bbentities,
						&event_types,
						&classes,
						&user_fields);

	if (n_entities < 1) return true;
	temp_created = new PK_ENTITY_t[n_entities]; // *FIX we should allocate this on the stack since it's a temporary array.
	temp_deleted = new PK_ENTITY_t[n_entities]; // *FIX we should allocate this on the stack since it's a temporary array.
	temp_altered = new PK_ENTITY_t[n_entities]; // *FIX we should allocate this on the stack since it's a temporary array.
	temp_transformed = new PK_ENTITY_t[n_entities]; // *FIX we should allocate this on the stack since it's a temporary array.

	assert(temp_created);
	assert(temp_deleted);
	assert(temp_altered);
	assert(temp_transformed);

	num_notable_events = 0;
	if (error)
		return false;
	assert(n_entities >= 0);
	num_entities = n_entities; // for type conversion only, so we can consistently use unsigned longs


	//fprintf(s_fp, "\n\n\n\n");
	for (i = 0; i < num_entities; i++)
	{
		bool result;
		//fprintf(s_fp, "i = %d, event number %d, entity number %d, event type %d\n", i, events[i], bbentities[i], event_types[i]);
		if (event_types[i] == PK_BB_event_merge_c)
		{
			unsigned long j;

			event_types[i] = PK_BB_event_change_c;
			for (j = i + 1; (j < num_entities) && (events[j] == events[i]); j++)
			{
				// all events following a merge event with the same event
				// number can be considered as delete events.
				event_types[j] = PK_BB_event_delete_c;
			}
		}
		if (event_types[i] == PK_BB_event_split_c)
		{
			unsigned long j;

			event_types[i] = PK_BB_event_change_c;
			for (j = i + 1; (j < num_entities) && (events[j] == events[i]); j++)
			{
				// all events following a merge event with the same event
				// number can be considered as delete events.
				event_types[j] = PK_BB_event_create_c;
			}
		}
		result = FilterEvent(bbentities[i],
			                  event_types[i],
							  num_entities,
							  temp_created,
							  &temp_num_created,
							  temp_deleted,
							  &temp_num_deleted,  // *FIX compact these 8 pointers into a single structure to decrease overhead of this function call
							  temp_altered,
							  &temp_num_altered,
							  temp_transformed,
							  &temp_num_transformed);
		assert(result);
	}
	PK_MEMORY_free(event_types);
	event_types = 0;
	PK_MEMORY_free(bbentities);
	bbentities = 0;
	temp_num = 0;
	CompressAndAllocEventArray(temp_created, temp_num_created, created, num_created);
	CompressAndAllocEventArray(temp_deleted, temp_num_deleted, deleted, num_deleted);
	CompressAndAllocEventArray(temp_altered, temp_num_altered, altered, num_altered);
	CompressAndAllocEventArray(temp_transformed, temp_num_transformed, transformed, num_transformed);
	delete temp_created;
	delete temp_deleted;
	delete temp_altered;
	delete temp_transformed;
	return true;
}

bool HP_BulletinBoard::CompressAndAllocEventArray(PK_ENTITY_t* from_array,
												  unsigned long num_from_entries,
												  PK_ENTITY_t** to_array,
												  unsigned long* num_to_entries)
{
	unsigned long i;
	unsigned long num_entries_to_allocate = 0;
	unsigned long j;
	PK_ERROR_t error;

	for (i = 0; i < num_from_entries; i++)
	{
		if (from_array[i])
			num_entries_to_allocate++;
	}
	if (num_entries_to_allocate)
	{
		error = PK_MEMORY_alloc(num_entries_to_allocate * sizeof(PK_ENTITY_t), (void**) to_array);
		assert(!error);
		if (error) return false;
	}

	j = 0;
	for (i = 0; i < num_from_entries; i++)
	{
		if (from_array[i]) // don't bother copying zero (nullified) entries
			(*to_array)[j++] = from_array[i];
	}
	*num_to_entries = j;
	return true;
}


void HP_BulletinBoard::UpdateBulletins()
{
}

void HP_BulletinBoard::CreateBB()
{
	PK_CLASS_t classes[3];

	PK_BB_sf_t bulletinForm;

	classes[0] = PK_CLASS_face;
	classes[1] = PK_CLASS_edge;
	classes[2] = PK_CLASS_body;  // note that not all operations are valid to specify for bodies.
	// we will include or exclude bodies by modifying the lengths member of the bulletinForms accordingly below.
	bulletinForm.create.array = classes;
	bulletinForm.deleet.array = classes;
	bulletinForm.copy.array = classes;
	bulletinForm.transfer.array = classes;
	bulletinForm.merge.array = classes;
	bulletinForm.split.array = classes;
	bulletinForm.transform.array = classes;
	bulletinForm.change_attrib.array = classes;
	bulletinForm.change.array = classes;


	bulletinForm.create.length = 3;
	bulletinForm.deleet.length = 3;
	bulletinForm.merge.length = 3;
	bulletinForm.copy.length = 0;  // not interested in copy operations
	bulletinForm.transfer.length = 2;  // not valid for bodies
	bulletinForm.split.length = 3;
	bulletinForm.transform.length = 3;
	bulletinForm.change_attrib.length = 3;
	bulletinForm.change.length = 2;  // this operation not valid to specify for bodies

	PK_BB_create(&bulletinForm, &m_BB);

}

